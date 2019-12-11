

with open('input') as f:
    map = [[c for c in line] for line in f.read().strip().split('\n')]

print(map)
column = len(map)
row = len(map[0])


new_orleans_map = [[0 * i for i in range(column)] for j in range(row)]
for k in range(column):
    for l in range(row):
        new_orleans_map[k][l] = 0
        for i in range(column):
            for j in range(row):
                if map[i][j] == "#" and (i+k) % 2 == 0 and (l+j) % 2 == 0:
                    if map[(i+k)//2][(l+j)//2] == ".":
                        new_orleans_map[k][l] += 1

for line in new_orleans_map:
    print(line)
