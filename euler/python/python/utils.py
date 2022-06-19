from itertools import takewhile


def take_lt(upper, itr):
    return takewhile(lambda x: x < upper, itr)
