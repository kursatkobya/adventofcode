#!/usr/bin/python3
universe = {}


def update_map(parent: str, orbit: str):
    if parent in universe:
        orbit_list = universe[parent]
        orbit_list.append(orbit)
    else:
        orbit_list = [orbit]
    universe[parent] = orbit_list


def count_planet_orbits(planet :str) -> int:
    count = 0
    if planet not in universe:
        return 0
    for orbit in universe[planet]:
        count += 1 + count_planet_orbits(orbit)
    return count


def has_santa(planet :str) -> bool:
    if planet not in universe:
        return False
    if 'SAN' in universe[planet]:
        return True
    return any(has_santa(child) for child in universe[planet])


def has_you(planet :str) -> bool:
    if planet not in universe:
        return False
    if 'YOU' in universe[planet]:
        return True
    return any(has_you(child) for child in universe[planet])


def whatislove():
    for planet in universe:
        if has_you(planet) and has_santa(planet):
            print(count_planet_orbits(planet))

with open("input", "r") as orbits:
    data = orbits.read().strip().split('\n')
    for line in data:
        parent, orbit = line.split(')')
        update_map(parent, orbit)

# test
# test_input = ("COM)B", "B)C", "C)D", "D)E", "E)F", "B)G", "G)H", "D)I", "E)J",
#              "J)K", "K)L")

#for l in test_input:
#    parent, orbit = l.split(')')
#    update_map(parent, orbit)

print(sum([count_planet_orbits(planet) for planet in universe]))
print(has_santa("COM"))
print(has_you("COM"))
whatislove()
