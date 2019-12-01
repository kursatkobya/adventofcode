#!/usr/bin/python3

with open("input", "r") as day1_input:
    total_fuel = 0
    extra_fuel = 0
    for line in day1_input:
        fuel_needed = int(int(line)/3) - 2
        total_fuel += fuel_needed
        extra_fuel_needed = 0
        while fuel_needed > 0:
            fuel_needed = int(fuel_needed/3) - 2
            if fuel_needed < 0:
                fuel_needed = 0
            extra_fuel_needed += fuel_needed

        extra_fuel += extra_fuel_needed

    print("Total fuel necessity : {}".format(total_fuel))
    print("Sum of fuel requirements : {}".format(total_fuel + extra_fuel))
