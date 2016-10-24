import numpy as np
from matplotlib import pyplot as plt
from matplotlib.ticker import FormatStrFormatter


file = open('thetas.dat')

lines = file.readlines();

thetas = np.zeros(len(lines))

i = 0;
for line in lines:
	thetas[i] = float(line)
	i += 1

n = len(thetas)
x = np.arange(0, n)
A = np.vstack([x, np.ones(len(x))]).T
m, c = np.linalg.lstsq(A, thetas)[0]

print("Slope = ", m)
mercYears = 415.2091 
precArcSec = m*mercYears*60*60
print("Arcseconds per century = ", precArcSec)
print("No of data points = ", n)

fig, ax = plt.subplots()

ax.yaxis.set_major_formatter(FormatStrFormatter('%.2e'))

plt.title(r"Perihelion precession of Mercury, dt = 1e-7")
plt.xlabel(r"No of orbits")
plt.ylabel(r"Angle")
plt.plot(x, thetas, '.')
plt.plot(x, m*x + c, 'r', label='Fitted line')
plt.text(0.3, 0.8,'Slope = ' + str(m),
     horizontalalignment='center',
     verticalalignment='center',
     transform = ax.transAxes)
plt.show()

