'''
A comparison of ground state with different angular momentum
omega = 0.01, 0.1, 1, 5
N = 200
rho = 5 for all
'''

import numpy as np
from matplotlib import pyplot as plt

n = 200

file1 = open('../data/omega0.01int.txt')
file2 = open('../data/omega0.5int.txt')
file3 = open('../data/omega1int.txt')
file4 = open('../data/omega5int.txt')

allLines1 = file1.readlines()
allLines2 = file2.readlines()
allLines3 = file3.readlines()
allLines4 = file4.readlines()

u1 = np.zeros(n)
u2 = np.zeros(n)
u3 = np.zeros(n)
u4 = np.zeros(n)

i = 0
for line in allLines1:
	u1[i] = float(line)
	i += 1
	if i >= n:
		break

file1.close()

i = 0
for line in allLines2:
	u2[i] = float(line)
	i += 1
	if i >= n:
		break

file2.close()

i = 0
for line in allLines3:
	u3[i] = float(line)
	i += 1
	if i >= n:
		break

file3.close()

i = 0
for line in allLines4:
	u4[i] = float(line)
	i += 1
	if i >= n:
		break

file4.close()

u1 = np.abs(u1)**2
u2 = np.abs(u2)**2
u3 = np.abs(u3)**2
u4 = np.abs(u4)**2

plt.plot(u1, label=r"$\omega_r=0.01$")
plt.plot(u2, label=r"$\omega_r=0.5$")
plt.plot(u3, label=r"$\omega_r=1$")
plt.plot(u4, label=r"$\omega_r=5$")

plt.legend(loc=2)
plt.title("Ground state with different angular momentum")
plt.xlabel(r'$\rho$', fontsize=20)
plt.ylabel(r'$ \mid{u(\rho)}\mid^2$', fontsize=20)

plt.show()
