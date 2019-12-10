from typing import List


ADD = 1
MULT = 2
INPUT = 3
OUTPUT = 4
JNZ = 5
JZ = 6
LT = 7
EQ = 8
REL = 9
HALT = 99

lengths = {
   ADD: 4,
   MULT: 4,
   INPUT: 2,
   OUTPUT: 2,
   JNZ: 3,
   JZ: 3,
   LT: 4,
   EQ: 4,
   REL: 2,
   HALT: 1
}


class Intcode(object):

    def __init__(self, instructions: str, inputs: List[int]):
        self.inputs = inputs
        self.codes = [int(code) for code in instructions.split(',')] + [0]*1000
        self.ip = 0
        self.rp = 0
        self.linked = None
        self.outputs = []
        self.halted = False

    def set_link(self, amp: List):
        self.linked = amp

    def get_modes(self) -> (int, int, int, int):
        op = str(self.codes[self.ip]).zfill(5)
        m3, m2, m1, opcode = int(op[0]), int(op[1]), int(op[2]), int(op[3:])
        return m1, m2, m3, opcode

    def get_value(self, mode: int, value: int) -> int:
        if mode == 0:
            return self.codes[value]
        elif mode == 1:
            return value
        elif mode == 2:
            return self.codes[self.rp + value]

    def set_value(self, mode: int, value: int, result: int):
        if mode == 0:
            self.codes[value] = result
        else:
            self.codes[self.rp + value] = result

    def process_instruction(self) -> bool:
        opcode = self.codes[self.ip] % 100
        length = lengths[opcode]
        m1, m2, m3, op = self.get_modes()
        vals = self.codes[self.ip + 1:self.ip + length]

        if op in [ADD, MULT, LT, EQ]:
            v1, v2, v3 = vals
            v1, v2 = self.get_value(m1, v1), self.get_value(m2, v2)
            if op == ADD:
                result = v1 + v2
            elif op == MULT:
                result = v1 * v2
            elif op == LT:
                result = int(v1 < v2)
            elif op == EQ:
                result = int(v1 == v2)
            self.set_value(m3, v3, result)
            self.ip += 4
        elif op in [JNZ, JZ]:
            v1, v2 = vals
            v1, v2 = self.get_value(m1, v1), self.get_value(m2, v2)
            if (op == JNZ and v1 != 0) or (op == JZ and v1 == 0):
                self.ip = v2
            else:
                self.ip += 3
        elif op in [INPUT, OUTPUT, REL]:
            v1 = vals[0]
            if op == INPUT:
                if len(self.inputs) == 0:
                    return False
                self.set_value(m1, v1, self.inputs.pop(0))
            elif op == OUTPUT:
                out = self.get_value(m1, v1)
                self.outputs.append(out)
                if self.linked is not None:
                    self.linked.inputs.append(out)
                    self.ip += 2
                    return False
            elif op == REL:
                self.rp += self.get_value(m1, v1)
            self.ip += 2
        else:
            self.halted = True
            return False

        return True

    def run(self) -> int:
        while self.process_instruction():
            pass
        if self.halted:
            return self.outputs[-1]
