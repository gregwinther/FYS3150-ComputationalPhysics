import numpy as np
import matplotlib.pyplot as plt
import matplotlib.mlab as mlab
from matplotlib import rc
from scipy import special
c= 60 #Number of cores!
T,E,Cv,M,X,Mabs,Nacc = np.loadtxt("../data/expectations1.dat",usecols=(0,1,2,3,4,5,6), unpack=True)
Ts,Es,Cvs,Ms,Xs,Mabss,Naccs = np.loadtxt("../data/expectations24_2.dat",usecols=(0,1,2,3,4,5,6), unpack=True)
#cycles = len(T)
#time = range(cycles)
weights = np.ones_like(E[20000:])/len(E[20000:])

sigma = np.mean(Cv)*np.mean(T)**2
sigmaT1 = np.var(E)
sigmaT24 = np.var(Es)
print sigma, sigmaT1, sigmaT24
# ---------------- New color scheme -----------------
# These are the "Tableau 20" colors as RGB.    
tableau20 = [(31, 119, 180), (174, 199, 232), (255, 127, 14), (255, 187, 120),    
             (44, 160, 44), (152, 223, 138), (214, 39, 40), (255, 152, 150),    
             (148, 103, 189), (197, 176, 213), (140, 86, 75), (196, 156, 148),    
             (227, 119, 194), (247, 182, 210), (127, 127, 127), (199, 199, 199),    
             (188, 189, 34), (219, 219, 141), (23, 190, 207), (158, 218, 229)]    
  
# Scale the RGB values to the [0, 1] range, which is the format matplotlib accepts.    
for i in range(len(tableau20)):    
    r, g, b = tableau20[i]    
    tableau20[i] = (r / 255., g / 255., b / 255.) 
#-------------------------------------------------------
fig = plt.figure()
#Equilibrium around 3e5/c=5000
plt.subplot(211)
plt.hist(E[20000:],2,color=tableau20[2],weights=weights)#,range=[-2.0, -1.8])
plt.title('Energy probability after EQ T=1',fontsize=12)
plt.ylabel('Probability',fontsize=10)
#plt.xlabel('Energy',fontsize=10)
#--------------------Configuration------------------------------
# Remove the plot frame lines. They are unnecessary chartjunk.    
ax = plt.subplot(211)  
ax.yaxis.grid()  
ax.spines["top"].set_visible(False)    
ax.spines["bottom"].set_visible(False)    
ax.spines["right"].set_visible(False)    
ax.spines["left"].set_visible(False)   
plt.xticks(fontsize=10)    
plt.yticks(fontsize=10)    
#plt.grid(b=True, which='major')
#plt.grid(b=True, which='minor', alpha=0.2)
#plt.minorticks_on()
# Remove the tick marks; they are unnecessary with the tick lines we just plotted.    
plt.tick_params(axis="both", which="both", bottom="off", top="off",    
                labelbottom="on", left="off", right="off", labelleft="on")  
plt.xlim(-2,2)
#plt.ylim(0,0.4)
#-------------------------------------------------------------#
plt.subplot(212)

weights = np.ones_like(Es[:])/len(Es[:])
plt.hist(Es[:],25,color=tableau20[2],weights = weights)#,range=[-1.27, -1.21])
plt.title('Energy probability after EQ T=2.4',fontsize=12)
plt.ylabel('Probability',fontsize=10)
plt.xlabel('Energy',fontsize=10)
#--------------------Configuration------------------------------
# Remove the plot frame lines. They are unnecessary chartjunk.    
ax = plt.subplot(212)  
ax.yaxis.grid()  
ax.spines["top"].set_visible(False)    
ax.spines["bottom"].set_visible(False)    
ax.spines["right"].set_visible(False)    
ax.spines["left"].set_visible(False)   
#plt.xticks(fontsize=10)    
#plt.yticks(fontsize=10)    
#plt.grid(b=True, which='major')
#plt.grid(b=True, which='minor', alpha=0.2)
#plt.minorticks_on()
# Remove the tick marks; they are unnecessary with the tick lines we just plotted.    
plt.tick_params(axis="both", which="both", bottom="off", top="off",    
                labelbottom="on", left="off", right="off", labelleft="on")  
plt.xlim(-2,2)
#plt.ylim(0,0.3)
#-------------------------------------------------------------
# if you want/need to save the plot in some format, you can use
# (bbox and pad make the figure to be tighten to the plot-box)
#fig.savefig('EhistProbBothT.pdf', bbox_inches='tight',pad_inches=0.106)
plt.show()