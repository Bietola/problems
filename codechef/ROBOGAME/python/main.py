def todigit(c):
    return int(ord(c) - ord('0'))

def solve(robofield):
    ln = None
    d = 0
    for c in robofield:
        if c == '.':
            d += 1
        else:
            if ln != None:
                if d - todigit(c) <= ln:
                    return "unsafe"
            d = 0
            ln = todigit(c)
    return "safe"

T = int(input())
for _ in range(T):
    robofield = str(input())
    print(solve(robofield))

