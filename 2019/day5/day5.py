#!/usr/bin/python3
from typing import List, Iterable


def get_param(input_array: List[int], index: int, mode: int) -> int:
    if mode == 0:
        return input_array[input_array[index]]
    return input_array[index]


def alarma(input_array: List[int]):
    index = 0
    while input_array[index] is not 99:
        opmodes = (int(input_array[index] / 100) % 10,
                   int(input_array[index] / 1000) % 10)
        opcode = input_array[index] % 100
        if opcode == 1:
            parameter1 = get_param(input_array, index+1, opmodes[0])
            parameter2 = get_param(input_array, index+2, opmodes[1])
            input_array[input_array[index+3]] = parameter1 + parameter2
            index += 4
        elif opcode == 2:
            parameter1 = get_param(input_array, index+1, opmodes[0])
            parameter2 = get_param(input_array, index+2, opmodes[1])
            input_array[input_array[index+3]] = parameter1 * parameter2
            index += 4
        elif opcode == 3:
            input_array[input_array[index+1]] = int(input("Shoot!: "))
            index += 2
        elif opcode == 4:
            print(input_array[input_array[index+1]])
            index += 2
        elif opcode == 5:
            parameter1 = get_param(input_array, index+1, opmodes[0])
            parameter2 = get_param(input_array, index+2, opmodes[1])
            if parameter1 is not 0:
                index = parameter2
            else:
                index += 3
        elif opcode == 6:
            parameter1 = get_param(input_array, index+1, opmodes[0])
            parameter2 = get_param(input_array, index+2, opmodes[1])
            if parameter1 is 0:
                index = parameter2
            else:
                index += 3
        elif opcode == 7:
            parameter1 = get_param(input_array, index+1, opmodes[0])
            parameter2 = get_param(input_array, index+2, opmodes[1])
            parameter3 = input_array[index+3]
            if parameter1 < parameter2:
                input_array[parameter3] = 1
            else:
                input_array[parameter3] = 0
            index += 4
        elif opcode == 8:
            parameter1 = get_param(input_array, index+1, opmodes[0])
            parameter2 = get_param(input_array, index+2, opmodes[1])
            parameter3 = input_array[index+3]
            if parameter1 == parameter2:
                input_array[parameter3] = 1
            else:
                input_array[parameter3] = 0
            index += 4


data: List[int]
with open('input') as f:
    data = [int(num) for num in f.read().strip().split(',')]
    alarma(data)
