import random
import math
import sys

N = int(sys.argv[1])

print("Generating", N, "bodies")

lim = [-10 * N**(1/3), 10 * N**(1/3)]

print(N / (lim[1] - lim[0])**3)

bodies = []

omega = float(sys.argv[3])

for i in range(N):
    x, y, z = [random.uniform(*lim) for i in range(3)]
    r = math.sqrt(x**2 + y**2 + z**2)
    if r <= lim[1]:
        v = r * omega
        vx = -y * v
        vy = v * x
        vz = 0
        m = 1
        bodies.append((x,y,z, vx, vy, vz, m))
 

f = open(sys.argv[2], "w")


for b in bodies:
    for c in b:
        f.write(str(c) + " ")
    f.write("\n")
        
def sphere(lim, omega):
    bodies = []
    vz = 0
    m = 1
    for i in range(N):
        x, y, z = [random.uniform(*lim) for i in range(3)]
        r = math.sqrt(x**2 + y**2 + z**2)
        if r <= lim[1]:
            v = r * omega
            vx = -y * v
            vy = v * x
            bodies.append((x,y,z, vx, vy, vz, m))






