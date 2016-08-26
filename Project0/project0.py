'''
Zeroth project in FYS3150

@author sebastwi
'''

import numpy as np
from matplotlib import pyplot as plt

f = lambda x: np.arctan(x);

def forwardEuler(x, h):
	return (f(x + h) - f(x)) / h;

h = np.array([0.01, 0.05, 0.1]);
x = np.sqrt(2);

print();