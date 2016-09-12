import sys
import numpy as np
import matplotlib.pyplot as plt
plt.rc('font', **{'family': 'serif', 'serif': ['Computer Modern']})
plt.rc('text', usetex=True)
plt.rcParams['xtick.labelsize'] = 18
plt.rcParams['ytick.labelsize'] = 18

# Opening file and declaring variables
file = sys.argv[1]
f = open(file,'r')
n = int(f.readline())
x = np.zeros(n+2)
u = np.zeros(n+2)
v = np.zeros(n+2)

# Extracting date
k = 0
next(f)
for line in f:
    x[k] = line.split()[0]
    u[k] = line.split()[1]
    v[k] = line.split()[2]
    k += 1

# Plotting
plt.plot(x, u, '-b', label="Amalytic solution")
plt.plot(x, v, '--r', label="Numerical solution")
plt.title('n =' + str(n), fontsize=18)
plt.xlabel(r'$x_i$', fontsize=20)
plt.ylabel(r'$u(x_i) \quad \& \quad  v_i$', fontsize=20)
plt.legend(fontsize=18)
plt.show()
