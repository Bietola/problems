from itertools import count, takewhile
from heapq import merge
import fire


def solve(upper):
    return sum(takewhile(lambda x: x < upper,
                         merge(count(3, 3), count(5, 5))))
    - sum(takewhile(lambda x: x < upper, count(15, 15)))


def cli(upper):
    print(solve(upper))


fire.Fire(cli)
