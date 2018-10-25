# N -> number of problem instances
# x -> potato weight
# y -> tomato weight
# n -> potato number available
# m -> tomato number available
# required: x*n == y*m

import math

def solve(x, y, n, m):
    F = math.gcd(x, y);
    return m >= x // F and n >= y // F;

# main
N = int(input());
for _ in range(N):
    x, y, n, m = map(int, input().split(" "));
    print("YES" if solve(x, y,n, m) else "NO");
