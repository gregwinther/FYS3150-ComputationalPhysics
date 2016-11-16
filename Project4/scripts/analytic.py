import numpy as np 
from matplotlib import pyplot as plt 

N = 4
temp = 1.0

exp_E     = -8*np.sinh(8/temp)/(3 + np.cosh(8/temp))
exp_M     = 0
exp_M_abs = 2*(np.exp(8/temp) + 2)/(np.cosh(8/temp) + 3) 
C_v       = (64./(temp*temp))*(np.cosh(8/temp)/(3 + np.cosh(8/temp))\
			 - (np.sinh(8/temp)/(3+np.cosh(8/temp)))**2)
X         = (8./temp) * (np.exp(8./temp) + 1)/(3+np.cosh(8./temp))
X_abs     = (4./(temp*(np.cosh(8./temp) + 3)))*(2*(np.exp(8./temp) + 1)\
			 - ((np.exp(8./temp)+2)**2)/(np.cosh(8./temp)+3))


print(exp_E/N)
print(exp_M/N)
print(exp_M_abs/N)
print(C_v/N)
print(X/N)
print(X_abs/N)