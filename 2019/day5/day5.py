#!/usr/bin/python3


with open("input", "r") as day2_input:
    input_array = day2_input.readline().split(",")


def get_param(index: int, mode: int) -> int:
    if mode == 0:
        return int(input_array[int(input_array[index])])
    return int(input_array[index])


def alarma():
    index = 0
    while int(input_array[index]) is not 99:
        opmodes = (int(int(input_array[index]) / 100) % 10,
                   int(int(input_array[index]) / 1000) % 10,
                   int(int(input_array[index]) / 10000) % 10)
        opcode = int(input_array[index]) % 100
        if opcode == 1:
            parameter1 = get_param(index+1, opmodes[0])
            parameter2 = get_param(index+2, opmodes[1])
            input_array[int(input_array[index+3])] = str(parameter1 +
                                                         parameter2)
            index += 4
        elif opcode == 2:
            parameter1 = get_param(index+1, opmodes[0])
            parameter2 = get_param(index+2, opmodes[1])
            input_array[int(input_array[index+3])] = str(parameter1 *
                                                         parameter2)
            index += 4
        elif opcode == 3:
            input_array[int(input_array[index+1])] = int(input("Shoot!: "))
            index += 2
        elif opcode == 4:
            print(input_array[int(input_array[index+1])])
            index += 2
        elif opcode == 5:
            parameter1 = get_param(index+1, opmodes[0])
            parameter2 = get_param(index+2, opmodes[1])
            if parameter1 is not 0:
                index = parameter2
            else:
                index += 3
        elif opcode == 6:
            parameter1 = get_param(index+1, opmodes[0])
            parameter2 = get_param(index+2, opmodes[1])
            if parameter1 is 0:
                index = parameter2
            else:
                index += 3
        elif opcode == 7:
            parameter1 = get_param(index+1, opmodes[0])
            parameter2 = get_param(index+2, opmodes[1])
            parameter3 = int(input_array[index+3])
            if parameter1 < parameter2:
                input_array[parameter3] = 1
            else:
                input_array[parameter3] = 0
            index += 4
        elif opcode == 8:
            parameter1 = get_param(index+1, opmodes[0])
            parameter2 = get_param(index+2, opmodes[1])
            parameter3 = int(input_array[index+3])
            if parameter1 == parameter2:
                input_array[parameter3] = 1
            else:
                input_array[parameter3] = 0
            index += 4


alarma()
