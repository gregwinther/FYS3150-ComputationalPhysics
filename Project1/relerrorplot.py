from matplotlib import pyplot as plt
#plt.rc('font', **{'family': 'serif', 'serif': ['Computer Modern']})
#plt.rc('text', usetex=True)
#plt.rcParams['xtick.labelsize'] = 18
#plt.rcParams['ytick.labelsize'] = 18

n = [10, 100, 1000, 10000, 10000, 1000000]
logsh=[-1.04139,-2.00432,-3.0043,-4.00004,-5,-6]
eps = [-1.1797,-3.08804, -5.08005,-7.07936,-9.00478,-6.77137]

plt.plot(logsh, eps, '-ob')
plt.title("Plot of maximal relative error vs step size", fontsize=18)
plt.xlabel(r'$log_{10}(h)$', fontsize=20)
plt.ylabel(r'$max(log_{10}(|(u_i-v_i)/u_i|)$', fontsize=20)
plt.show()
