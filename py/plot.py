from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import numpy as np
import math
from itertools import product, combinations
import sys

def draw_cuboid(x, y, z, ax, c='b'):
    # draw cuboid
    max_diff = [x[1] - x[0], y[1] - y[0], z[1] - z[0]]
    plots = []
    for s, e in combinations(np.array(list(product(x, y, z))), 2):
        if np.sum(np.abs(s-e) == max_diff) == 1 + len(max_diff) - np.count_nonzero(max_diff):
                plots.append(ax.plot3D(*zip(s, e), color=c))
    return plots

def draw_cuboids(cuboids, ax):
    plots = []
    for i, c in enumerate(cuboids):
        plots += draw_cuboid(*c, ax)
    return plots

file_object = open(sys.argv[1],"r")
a = file_object.readlines()
positions = []
complete_positions = []
count = 0
min_pos = math.inf
max_pos = -math.inf
for i in range(len(a)):
    if len(a[i].split()) < 3:
        positions_in_time_step = np.array(positions)
        if np.max(positions_in_time_step) > max_pos:
            max_pos = np.max(positions_in_time_step)
        if np.min(positions_in_time_step) < min_pos:
            min_pos = np.min(positions_in_time_step)
        complete_positions.append(np.array(positions_in_time_step))
        count += 1
        positions = []
    else:
        positions.append([float(x) for x in a[i].split()])


if len(sys.argv) > 2:
    f = open(sys.argv[2], "r")

    complete_cuboids = []

    cuboids = []
    for line in f:
        split_line = line.split()
        if len(split_line) == 0:
            complete_cuboids.append(cuboids)
            cuboids = []
        elif len(split_line) == 3:
            mc = [float(i) for i in split_line]
        else:
            x_min, x_max, y_min, y_max, z_min, z_max = [float(i) for i in split_line]
            cuboids.append([[x_min, x_max], [y_min, y_max], [z_min, z_max]]) 


fig = plt.figure()
ax = fig.gca(projection='3d')

for i in range(0, len(complete_positions)):
    ax.set_xlim(min_pos,max_pos)
    ax.set_ylim(min_pos,max_pos)
    ax.set_zlim(min_pos,max_pos)
    p1 = ax.scatter(complete_positions[i][:,0], complete_positions[i][:,1], complete_positions[i][:,2], c='r', marker='o')
    ax.set_xlabel("x")
    ax.set_ylabel("y")
    ax.set_zlabel("z")
    ax.view_init(30, 0.5*i)
    if len(sys.argv) > 2:
        p2 = draw_cuboids(complete_cuboids[i], ax)
    plt.pause(0.0001)
    plt.cla()
