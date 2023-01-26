from itertools import permutations, combinations, product

inp = '''42879
35843
35843
29998
35440
49458
46622
48633
43216
33286
27119
31157
29931
49384
48981
54341
49597
9384
4698
4651
1924
1194
5981
2438
3116
6937
4247
49355
46937
61155
53116
69573
44163
38945
63079
65812
49355
46937
34664
45981
39928
45412
41955
37267
86030
57257
37513
61155
66054
59673
46937
50854
50704
50704
51121
50854
67161
65812
70194
51290
87971
59755
55474
67747
63371
65114
70245
55984
74975
88184
93083
97274
84376
60427
97313
92931
97364
64386
57685
76577
72531
92931
93173
60427
60405
61366
76100
97313
69998
60405
73741
69074
70335
12443
94866
73100
86874
79043
62559
94866'''

inp = list(enumerate(inp.split()))

tot = 54238 
print(list(filter(
    lambda x: int(x[0][1]) + int(x[1][1]) == tot,
    product(inp, inp)
)))
