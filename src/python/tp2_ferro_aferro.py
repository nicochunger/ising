#Grafica para el caso ferro-antiferro

import numpy as np
import matplotlib.pyplot as plt

path = "/home/nunger/Documents/ising/res/"

energia = np.loadtxt(path + "tp2_energia_faf.txt")
mag = np.loadtxt(path + "tp2_mag_faf.txt")
var_e = np.loadtxt(path + "tp2_varene_faf.txt")
var_m = np.loadtxt(path + "tp2_varmag_faf.txt")
temp = np.loadtxt(path + "tp2_temp_260.txt")

plt.style.use('seaborn-whitegrid')
plt.grid(b=True, which='mayor',color='k', linestyle='-')

#plt.plot(temp, mag, 'b.')
plt.plot(temp, mag, 'b.')
#print energia[0]
plt.title('Ferro-antiferro')
plt.xlabel(r'Temperatura $(T)$')
plt.ylabel('Magnetizacion media por sitio')
plt.show()
