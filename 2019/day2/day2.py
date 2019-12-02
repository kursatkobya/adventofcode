#!/usr/bin/python3


def alarma(first, second) -> int:
    with open("input", "r") as day2_input:
        input_array = day2_input.readline().split(",")
    input_array[1] = first
    input_array[2] = second
    index = 0
    while index < len(input_array):
        opcode = int(input_array[index])
        if opcode == 1:
            input_array[int(input_array[index+3])] = str(
                int(input_array[int(input_array[index+1])]) +
                int(input_array[int(input_array[index+2])]))
        elif opcode == 2:
            input_array[int(input_array[index+3])] = str(
                int(input_array[int(input_array[index+1])]) *
                int(input_array[int(input_array[index+2])]))
        elif opcode == 99:
            break
        index += 4

    return int(input_array[0])


def alarmb() -> int:
    for a in range(100):
        for b in range(100):
            if alarma(a, b) == 19690720:
                return (100*a + b)


print("side A : {}".format(alarma(12, 2)))
print("side B : {}".format(alarmb()))
