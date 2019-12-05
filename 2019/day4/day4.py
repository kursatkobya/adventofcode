#!/usr/bin/python3


def never_decrease(value) ->bool:
    return ((int(value/100000) <= int(value/10000) % 10) &
            (int(value/10000) % 10 <= int(value/1000) % 10) &
            (int(value/1000) % 10 <= int(value/100) % 10) &
            (int(value/100) % 10 <= int(value/10) % 10) &
            (int(value/10) % 10 <= value % 10))


def same_digits(value) ->bool:
    return ((int(value/100000) == int(value/10000) % 10) |
            (int(value/10000) % 10 == int(value/1000) % 10) |
            (int(value/1000) % 10 == int(value/100) % 10) |
            (int(value/100) % 10 == int(value/10) % 10) |
            (int(value/10) % 10 == value % 10))


def insane_digits(value) ->bool:
    value = str(value)
    return not 2 in [value.count(d) for d in '0123456789']


def possible_passwords(password_range) ->int:
    min_pwd, max_pwd = password_range.split('-')
    return (len([pwd for pwd in range(int(min_pwd), int(max_pwd))
            if never_decrease(pwd) and same_digits(pwd)]),
            len([pwd for pwd in range(int(min_pwd), int(max_pwd))
                if never_decrease(pwd) and same_digits(pwd) and
                not insane_digits(pwd)]))


assert same_digits(122345) is True
assert same_digits(111111) is True
assert never_decrease(111111) is True
assert never_decrease(111123) is True
assert never_decrease(135679) is True
assert insane_digits(112233) is False
assert insane_digits(123444) is True
assert insane_digits(111122) is False

print(possible_passwords("156218-652527"))
