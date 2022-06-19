from itertools import count, takewhile
from heapq import merge
from utils import take_lt
import fire


def fib():
    a = 1
    yield a
    b = 2
    yield b
    while True:
        a = a + b
        yield a
        b = b + a
        yield b


# 400000
def cli(upper):
    print(sum(take_lt(upper, filter(lambda x: x % 2 == 0, fib()))))


fire.Fire(cli)
