import numpy as np
import matplotlib
import matplotlib.pyplot as plt
import sys

plt.rc('text', usetex=True)
plt.rc('font', family='serif')

path = sys.argv[1]

files = ["time_1.txt", "time_2.txt", "time_4.txt", "time_8.txt", "time_16.txt", "time_32.txt", "time_64.txt"]
P = [1,2,4,8,16,32,64]


N = [100, 200, 500, 1000, 2000, 5000, 10000, 20000, 50000]

legend = ["$S_P = P$"]

markers = ['o', 'v', '8', 's', 'p', '+', 'D', '*', '^']

print(len(N), len(markers))

plt.figure(figsize=(8, 8))
plt.loglog(P, P, "--")
#plt.plot(P, P, "--")
for i, n in enumerate(N):
    T = []
    res_path = path + str(n) + "/"

    for f in files:
        t = np.loadtxt(res_path+f)
        t = t[:100]
        T.append(np.mean(t))

    #print(np.array(T))
    #print()
    #print()
    print(np.array(np.divide(T[0], T)))

    legend.append("$N = " + str(n) + "$")

    #plt.plot(P, T, 'o-', ms=5)
    plt.loglog(P, np.divide(T[0], T), '-', ms=5, marker=markers[i], lw=0.75)
    #plt.plot(P, np.divide(T[0], T), 'o-', ms=5)

plt.legend(legend, fontsize=14)
plt.xlabel("$P$", fontsize=16)
plt.ylabel("$S_P$", fontsize=16)
plt.tick_params(labelsize=14)
ax = plt.gca()
ax.set_yticks([1,2,4,8,16,32,64])
ax.get_yaxis().set_major_formatter(matplotlib.ticker.ScalarFormatter())
ax.set_xticks([1,2,4,8,16,32,64])
ax.get_xaxis().set_major_formatter(matplotlib.ticker.ScalarFormatter())

plt.savefig("speedup_loglog.pdf", format='pdf', dpi=1000)
#plt.show()
