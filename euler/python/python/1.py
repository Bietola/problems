from itertools import count, takewhile
from heapq import merge
import fire


def solve(upper):
    return sum(takewhile(lambda x: abs(x) < upper, map(
        lambda x: x / 2 if x % 15 == 0 else x,
        merge(count(3, 3), count(5, 5))
    )))


def cli(upper):
    print(solve(upper))


fire.Fire(cli)
