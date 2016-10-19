''' 
Simple plotting script
'''

import numpy as np;

file1 = open('positions.dat')

line = file1.readline()

print(line)
arraydings = np.fromstring(line, dtype=np.float, sep=" ")
print(arraydings)


file1.close()