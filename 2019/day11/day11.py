from intcode import Intcode
from collections import defaultdict

with open('input') as f:
    data = f.read().strip()

x, y = 0, 0
direction = 0
deltas = {0: (0, 1), 1: (1, 0), 2: (0, -1), 3: (-1, 0)}

panels = defaultdict(int)
panels[(0, 0)] = 1
computer = Intcode(data, [])
counter = 0
while not computer.halted:
    computer.inputs.append(panels[(x, y)])
    computer.run()
    color, turn = computer.outputs[-2:]
    panels[(x, y)] = color
    counter += 1
    if turn == 0:
        direction -= 1
    else:
        direction += 1
    direction %= 4
    dx, dy = deltas[direction]
    x += dx
    y += dy


print(counter * 6)
grid = [[0 for _ in range(50)] for _ in range(6)]

for panel, color in panels.items():
    x, y = panel
    grid[abs(y)][x] = color

for row in grid:
    print(''.join(['█' if c == 1 else ' ' for c in row]))
