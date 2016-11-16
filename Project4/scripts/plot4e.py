import numpy as np
import matplotlib.pyplot as plt
from matplotlib import rc
from scipy import special
#T (temperature), Cv (specific heat), X (susceptibility) 


T1,E1,Cv1,M1,X1,Mabs1= np.loadtxt("../data/expectations20.dat",usecols=(0,1,2,3,4,5), unpack=True)

T2,E2,Cv2,M2,X2,Mabs2 = np.loadtxt("../data/expectations40.dat",usecols=(0,1,2,3,4,5), unpack=True)

T3,E3,Cv3,M3,X3,Mabs3 = np.loadtxt("../data/expectations60.dat",usecols=(0,1,2,3,4,5), unpack=True)

T4,E4,Cv4,M4,X4,Mabs4 = np.loadtxt("../data/expectations80.dat",usecols=(0,1,2,3,4,5), unpack=True)

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
plt.subplot(411)
plt.plot(T1, E1,color=tableau20[2],label='L=40')
plt.plot(T2, E2,color=tableau20[4],label='L=60')
plt.plot(T3, E3,color=tableau20[6],label='L=100')
plt.plot(T4, E4,color=tableau20[8],label='L=140')
# Sjekk plott. Gaar fra 0 til 3500, 500 av gangen. 
# Gang med antall kjerner (32 i dette eksempelet).
#plt.xticks(np.arange(0,len(T),2500),np.arange(0,len(T)*c,2500*c))
plt.title(r'Expectation values for $L=20,40,60,80$')
plt.ylabel(r'$\langle E\rangle$',fontsize=16)

#--------------------Configuration------------------------------
# Remove the plot frame lines. They are unnecessary chartjunk.    
ax = plt.subplot(411)  
ax.yaxis.grid()  
ax.spines["top"].set_visible(False)    
ax.spines["bottom"].set_visible(False)    
ax.spines["right"].set_visible(False)    
ax.spines["left"].set_visible(False)   
plt.xticks(fontsize=10)    
plt.yticks(fontsize=10)    
plt.legend(loc=2, fontsize=10)
#plt.grid(b=True, which='major')
#plt.grid(b=True, which='minor', alpha=0.2)
#plt.minorticks_on()
# Remove the tick marks; they are unnecessary with the tick lines we just plotted.    
plt.tick_params(axis="both", which="both", bottom="off", top="off",    
                labelbottom="on", left="off", right="off", labelleft="on")  
#------------------------------------------------------------
#-------------------------------------------------------
plt.subplot(412)
plt.plot(T1, Mabs1,color=tableau20[2],label='L=40')
plt.plot(T2, Mabs2,color=tableau20[4],label='L=60')
plt.plot(T3, Mabs3,color=tableau20[6],label='L=100')
plt.plot(T4, Mabs4,color=tableau20[8],label='L=140')
# Sjekk plott. Gaar fra 0 til 3500, 500 av gangen. 
# Gang med antall kjerner (32 i dette eksempelet).
#plt.xticks(np.arange(0,len(T),2500),np.arange(0,len(T)*c,2500*c))
plt.ylabel(r'$\langle |M| \rangle $',fontsize=16)

#--------------------Configuration------------------------------
# Remove the plot frame lines. They are unnecessary chartjunk.    
ax = plt.subplot(412)  
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
#------------------------------------------------------------
#-------------------------------------------------------
plt.subplot(413)
plt.plot(T1, Cv1,color=tableau20[2],label='L=40')
plt.plot(T2, Cv2,color=tableau20[4],label='L=60')
plt.plot(T3, Cv3,color=tableau20[6],label='L=100')
plt.plot(T4, Cv4,color=tableau20[8],label='L=140')
# Sjekk plott. Gaar fra 0 til 3500, 500 av gangen. 
# Gang med antall kjerner (32 i dette eksempelet).
#plt.xticks(np.arange(0,len(T),2500),np.arange(0,len(T)*c,2500*c))
plt.ylabel(r'$C_V$',fontsize=16)

#--------------------Configuration------------------------------
# Remove the plot frame lines. They are unnecessary chartjunk.    
ax = plt.subplot(413)  
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
#------------------------------------------------------------
#-------------------------------------------------------
plt.subplot(414)
plt.plot(T1, X1,color=tableau20[2],label='L=20')
plt.plot(T2, X2,color=tableau20[4],label='L=40')
plt.plot(T3, X3,color=tableau20[6],label='L=60')
plt.plot(T4, X4,color=tableau20[8],label='L=80')
# Sjekk plott. Gaar fra 0 til 3500, 500 av gangen. 
# Gang med antall kjerner (32 i dette eksempelet).
#plt.xticks(np.arange(0,len(T),2500),np.arange(0,len(T)*c,2500*c))
plt.ylabel(r'$\chi$',fontsize=16)

plt.xlabel(r'$T$',fontsize=16)
#--------------------Configuration------------------------------
# Remove the plot frame lines. They are unnecessary chartjunk.    
ax = plt.subplot(414)  
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
#------------------------------------------------------------
#-------------------------------------------------------------
# if you want/need to save the plot in some format, you can use
# (bbox and pad make the figure to be tighten to the plot-box)
fig.savefig('largersystems.pdf', bbox_inches='tight',pad_inches=0.106)
plt.show()
