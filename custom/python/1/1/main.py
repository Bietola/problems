import fire
from math import sqrt
from itertools import takewhile, chain, count
from more_itertools import take, side_effect
from sortedcontainers import SortedSet


def drop(n, seq):
    itr = iter(seq)
    for i in range(n):
        try:
            next(itr)
        except StopIteration:
            return itr
    return itr


class Primes:
    _cache = SortedSet([1, 2, 3])

    def primes(self):
        return chain(self._cache, side_effect(
            lambda n: self._cache.add(n),
            filter(
                lambda n: all(map(
                    lambda d: n % d == 0,
                    takewhile(
                        lambda x: x <= sqrt(n),
                        self._cache[2:]
                    )
                )),
                count(self._cache[-1] + 2, 2)
            )
        ))

    def factors(self, n):
        for p in takewhile(
            lambda x: x <= sqrt(n),
            drop(1, self.primes())
        ):
            pw = 0
            fs = n
            while fs % p == 0:
                pw += 1
                fs /= p

            if pw > 0:
                yield (p, pw)


def primes_cli(start=1, end=100):
    print(list(
        take(end, drop(start, Primes().primes()))
    ))


def factors_cli(n):
    print(list(Primes().factors(n)))


if __name__ == '__main__':
    fire.Fire(factors_cli)
