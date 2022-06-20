from time import sleep
from threading import Thread
import fire


def sort(lst):
    out = []

    def go(n):
        sleep(n)
        out.append(n)

    ts = []
    for n in lst:
        t = Thread(go, (n,))
        ts.append(t)
        t.start()

    for t in ts:
        t.join()

    return out


def cli(*args):
    print(sort([*args]))


fire.Fire(cli)
