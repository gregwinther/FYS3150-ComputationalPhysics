from matplotlib import pyplot as plt 
import numpy as np 

data = np.loadtxt("../data/stuff2.dat")

plt.hist(data, bins = 100)
plt.show()