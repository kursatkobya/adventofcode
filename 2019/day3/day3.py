#!/usr/bin/python3
from typing import List


def direction(dir):
    return {
            'U': (0, 1),
            'D': (0, -1),
            'L': (-1, 0),
            'R': (1, 0),
    }[dir]


def serialize_data(data):
    steps, curr_x, curr_y = 0, 0, 0
    points = set()
    step_counts = {}

    for point in data.split(','):
        x, y = direction(point[:1])
        length = int(point[1:])
        for i in range(length):
            curr_x += x
            curr_y += y
            steps += 1
            points.add((curr_x, curr_y))
            step_counts[(curr_x, curr_y)] = steps
    return points, step_counts


def run(data1, data2):
    points1, steps1 = serialize_data(data1)
    points2, steps2 = serialize_data(data2)
    intersections = points1 & points2
    return (min(abs(x) + abs(y) for x, y in intersections),
            min(steps1[point] + steps2[point] for point in intersections))


assert run("R8,U5,L5,D3", "U7,R6,D4,L4") == (6, 30)
assert run("R75,D30,R83,U83,L12,D49,R71,U7,L72",
           "U62,R66,U55,R34,D71,R55,D58,R83") == (159, 610)
assert run("R98,U47,R26,D63,R33,U87,L62,D20,R33,U53,R51",
           "U98,R91,D20,R16,D67,R40,U7,R15,U6,R7") == (135, 410)

with open("input", "r") as wires:
    first_wire = wires.readline()
    second_wire = wires.readline()
    print("{}".format(run(first_wire, second_wire)))
