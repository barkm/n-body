import random
import math

def disk(orig, R, eps, N, omega):
    bodies = []
    for n in range(N):
        x = random.uniform(-R + orig[0], R + orig[0])
        y = random.uniform(-R + orig[1], R + orig[1])
        z = random.uniform(-eps + orig[2], eps + orig[2])
        r = math.sqrt((x-orig[0])**2 + (y-orig[1])**2)
        if r <= R:
            v = r * omega
            vx = -(y-orig[1]) * v
            vy = (x-orig[0]) * v
            bodies.append((x,y,z, vx, vy, 0, 1)) 
    return bodies


#bodies = disk([-1000, -1000, 0], 1000, 1, 1000, 0.000025)
#bodies += disk([1000, 1000, 0], 1000, 1, 1000, 0.000025)

bodies = disk([-400, -400, 0], 200, 1, 50, 0.000025)
bodies += disk([400, 400, 0], 200, 1, 50, 0.000025)

#bodies = disk([-1000, -1000, 1000], 1000, 1, 1000, 0.000025)
#bodies += disk([1000, 1000, -1000], 1000, 1, 1000, 0.000025)

#bodies = disk([-5000, -5000, 2000], 5000, 1, 25000, 0.0000025)
#bodies += disk([5000, 5000, -5000], 5000, 1, 25000, -0.0000025)

f = open("disk.txt", "w")
for b in bodies:
    for c in b:
        f.write(str(c) + " ")
    f.write("\n")
