from typing import List, Tuple
from math import gcd


with open('input') as f:
    map = [[c for c in line] for line in f.read().strip().split('\n')]

def locate_astroids(space_map: List[List[str]]) -> List[Tuple[int, int]]:
    column = len(space_map)
    row = len(space_map[0])
    astroids = []
    for k in range(column):
        for l in range(row):
             if space_map[k][l] == "#":
                 astroids.append((k, l))
    return astroids


def in_line_of_sight(astroid1: Tuple[int, int], astroid2: Tuple[int, int]) -> bool:
    dx, dy = abs(astroid2[0] - astroid1[0]), abs(astroid2[1] - astroid1[1])
    return gcd(dx, dy) == 1


def blocker_list(astroid1: Tuple[int, int], astroid2: Tuple[int, int]) -> List[Tuple[int, int]]:
    dx, dy = abs(astroid2[0] - astroid1[0]), abs(astroid2[1] - astroid1[1])
    if dx == 0 or dy == 0:
        steps = max(abs(dx), abs(dy))
    else :
        steps = gcd(abs(dx), abs(dy))
    return [(astroid1[0] + step * dx // steps, astroid1[1] + step * dy // steps)
            for step in range(1, steps)]


def can_see(astroid1: Tuple[int, int], astroid2: Tuple[int, int]) -> bool:
    if astroid1 == astroid2:
        return False
    if in_line_of_sight(astroid1, astroid2):
        return True
    return not any(ast in astroids for ast in blocker_list(astroid1, astroid2))


with open('input') as f:
    map = [[c for c in line] for line in f.read().strip().split('\n')]

astroids = locate_astroids(map)
views = {}
for ast in astroids:
    views[ast] = sum([can_see(ast, other) for other in astroids])

print(max(views.items(), key = lambda item: item[1]))
