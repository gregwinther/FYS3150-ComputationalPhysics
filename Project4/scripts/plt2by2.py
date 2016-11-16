import numpy as np 
from matplotlib import pyplot as plt


filename = "expectations60.dat"


Ts,Es,Cvs,Ms,Xs,Mabss = np.loadtxt(filename, usecols=(0,1,2,3,4,5), unpack=True)

plt.plot(Ts, Xs)
plt.xlabel("Temp")
plt.ylabel("E")
plt.title("L=60")
plt.show()