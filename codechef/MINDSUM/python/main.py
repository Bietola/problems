ef digitsum(num):
    if num == 0:
        return 0
    else:
        return digitsum(num // 10) + num % 10

j = None
state = "init"

for i in range(0, 100, int(input())):
    s = digitsum(i)
    if state == "init":
        state = "const"
        oldI = i
        print("[{}".format(i), end="")
    elif state == "const" and j is None or abs(s - j) != 1:
        state = "init"
        print("...{}]({})".format(i, i - oldI), end="\n")
    j = s
print()
