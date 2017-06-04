import random

import sys

N = int(sys.argv[1])

print("Generating", N, "bodies")

lim = [-10 * N**(1/3), 10 * N**(1/3)]

print(N / (lim[1] - lim[0])**3)

bodies = []


for i in range(N):
    bodies.append([random.uniform(*lim) for i in range(3)])
 

f = open(sys.argv[2], "w")


for b in bodies:
    for c in b:
        f.write(str(c) + " ")
    f.write("0 0 0 1")
    f.write("\n")
        






