import math
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import sys

path = sys.argv[1]


thfile = path + "thetas.txt"
pfile = path + "processes.txt"

thetas = [float(th) for th in open(thfile).read().split()]
P = [int(p) for p in open(pfile).read().split()]

T = []
R = []
for p in P:
    Rtmp = []
    Ttmp = []
    for th in thetas:
        #if math.floor(th) == th:
        #    th = int(th)
        f = open("{0}{1}/time_{2}.txt".format(path,p,th))
        t = [float(i) for i in f.read().splitlines()]
        Ttmp.append(np.mean(t))

        f = open("{0}{1}/tree_size_{2}.txt".format(path,p,th))
        r = [float(i) for i in f.read().splitlines()]
        Rtmp.append(np.mean(r))
            
    T.append(Ttmp)
    R.append(Rtmp)

plt.rc('text', usetex=True)
plt.rc('font', family='serif')

markers = ['-', '--', '-.', ':', (2, (10,2))]
    
plt.figure(figsize=(8, 8))
for i, t in enumerate(T):
    plt.plot(thetas, np.divide(T[0], t), '-', linestyle=markers[i])

plt.xlabel(r'$\theta$', fontsize=16)
plt.ylabel("$S_P$", fontsize=16)
plt.legend(["$P="+str(p)+"$" for p in P], fontsize=14)
plt.tick_params(labelsize=14)
plt.savefig("speedup_vs_theta.pdf", format='pdf', dpi=1000)

#plt.figure()
#for t in T:
#    plt.plot(thetas, t)
#
#plt.xlabel(r"$\theta$", fontsize=16)
#plt.ylabel("$T_P$", fontsize=16)
#plt.legend(["$P="+str(p)+"$" for p in P], fontsize=14)

plt.figure(figsize=(8, 8))
for r in R:
    plt.plot(thetas, r)

plt.xlabel(r"$\theta$", fontsize=16)
plt.ylabel("number of cells", fontsize=16)
plt.legend(["$P="+str(p)+"$" for p in P], fontsize=14, bbox_to_anchor=(0.875, 0.80), bbox_transform=plt.gcf().transFigure)
plt.tick_params(labelsize=14)
plt.savefig("treesize_vs_theta.pdf", format='pdf', dpi=1000)

#X, Y = np.meshgrid(P, thetas)
#
#fig = plt.figure()
#ax = fig.gca(projection='3d')
#Z = np.array(T).T
#Z = Z / Z[:,0].reshape(Z.shape[0], 1)
#Z = 1 / Z;
#ax.plot_wireframe(X, Y, Z)
#
#ax.set_xlabel('number of processes')
#ax.set_ylabel("theta")
#ax.set_zlabel('speedup')
#
#fig = plt.figure()
#ax = fig.gca(projection='3d')
#Z = np.array(R).T
#ax.plot_wireframe(X, Y, Z)
#
#ax.set_xlabel('number of processes')
#ax.set_ylabel("theta")
#ax.set_zlabel('tree size')
#
#fig = plt.figure()
#ax = fig.gca()
#cs = ax.contourf(X, Y, Z)
#plt.colorbar(cs)


#plt.show()
