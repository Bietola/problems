from itertools import dropwhile
from sortedcontainers import SortedSet

print(list(dropwhile(lambda x: x < 3, [1, 2, 5, 6, 7])))

print(list(dropwhile(lambda x: x < 3, [1, 2])))


def hello():
    n = 0
    for n in range(1, 10):
        print(n)

    print(n + 2)


i = iter([1, 2, 3])
next(i, 2)
list(i)


def drop(n, seq):
    itr = iter(seq)
    for i in range(n):
        try:
            next(itr)
        except StopIteration:
            return itr
    return itr


m = map(
    lambda x: x * 2,
    [1, 2, 3]
)
list(drop(400, m))
list(m)


s = SortedSet([1, 2, 3])
s[-1]
s
