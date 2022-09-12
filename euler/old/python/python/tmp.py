from itertools import count
from more_itertools import take

print(take(10, count(-10, -10)))
