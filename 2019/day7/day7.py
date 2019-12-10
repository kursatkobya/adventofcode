from intcode import Intcode
import itertools

with open('input') as f:
    data = f.read().strip()


def supply_thrusters(phases: int) -> int:
    amps = [Intcode(data, [a]) for a in phases]
    amps[0].inputs.append(0)

    for i in range(-1, len(amps)-1):
        amps[i].set_link(amps[i+1])

    for amp in amps:
        amp.run()

    return amps[-1].outputs[-1]


def supply_thrusters_looped(phases: int) -> int:
    amps = [Intcode(data, [a]) for a in phases]
    amps[0].inputs.append(0)

    for i in range(-1, len(amps)-1):
        amps[i].set_link(amps[i+1])

    i = 0
    while not amps[-1].halted:
        amps[i].run()
        i = (i + 1) % len(amps)
    return amps[-1].outputs[-1]


print(max([supply_thrusters(phase) for phase in
      itertools.permutations((0, 1, 2, 3, 4))]))
print(max([supply_thrusters_looped(phase) for phase in
      itertools.permutations((5, 6, 7, 8, 9))]))
