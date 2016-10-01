'''
Plot of a system w/o interaction and one w/ interaction
omega = 0.01, N = 200
'''

import sys
import numpy as np 
from matplotlib import pyplot as plt 

n = 200

file1 = open('../data/omega0.01int.txt')
file2 = open('../data/omega0.01noint.txt')

allLines1 = file1.readlines()
allLines2 = file2.readlines()

u1 = np.zeros(n)
u2 = np.zeros(n)

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

u1 = np.abs(u1)**2
u2 = np.abs(u2)**2

plt.title("Coulomb and no-interacting comparison "\
	 + r'$\omega_r = 0.01, N=200$')
plt.plot(u1, label="With Coulomb interaction")
plt.plot(u2, label="No interaction")
plt.xlabel(r'$\rho$', fontsize=20)
plt.ylabel(r'$ \mid{u(\rho)}\mid^2$', fontsize=20)
plt.legend(loc=2)
plt.show()