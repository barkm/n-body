import random

def uniform(limits, N):
    bodies = []
    for n in range(N):
        x, y= [random.uniform(*limits) for i in range(2)]
        z = random.uniform(-0.01, 0.01)
        bodies.append([x,y,z,0,0,0,1])
    return bodies


bodies = uniform([-100, 100], 50)

f = open("uniform.txt", "w")
for b in bodies:
    for c in b:
        f.write(str(c) + " ")
    f.write("\n")
