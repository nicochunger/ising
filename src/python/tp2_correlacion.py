#Correlaciones

import numpy as np
import matplotlib.pyplot as plt

path = "/home/nunger/Documents/ising/res/"

corr1 = np.loadtxt(path + "tp2_corr_e_t_0.txt")
corr2 = np.loadtxt(path + "tp2_corr_e_t_50.txt")
corr3 = np.loadtxt(path + "tp2_corr_e_t_100.txt")
corr4 = np.loadtxt(path + "tp2_corr_e_t_150.txt")
corr5 = np.loadtxt(path + "tp2_corr_e_t_200.txt")
corr6 = np.loadtxt(path + "tp2_corr_e_t_250.txt")

#plt.figure(0)
plt.style.use('seaborn-whitegrid')

plt.plot(corr6, label='T=0.25')
plt.plot(corr5, label='T=1.5')
plt.plot(corr4, label='T=2.3')
plt.plot(corr3, label='T=2.8')
plt.plot(corr2, label='T=3.75')
plt.plot(corr1, label='T=5')

plt.xlabel('Nro de pasos de metropolis')
plt.ylabel('Funcion de correlacion')

plt.legend(loc=2)

#plt.grid(b=True, which='mayor',color='k', linestyle='-')

plt.show()
