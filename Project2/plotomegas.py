import sys
import numpy as np 
from matplotlib import pyplot as plt 

file = open('data.txt')

n = 250

allLines = file.readlines()

u = np.zeros(n)

i = 0
for line in allLines:
	u[i] = float(line)
	i += 1
	if i >= n:
		break

file.close()

u = np.abs(u)**2

plt.plot(u)
plt.show()