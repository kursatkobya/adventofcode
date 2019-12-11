from intcode import Intcode
with open('input') as f:
    instructions = f.read().strip()

print(Intcode(instructions, [1]).run())
print(Intcode(instructions, [2]).run())
