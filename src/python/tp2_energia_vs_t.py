# Programa para testear pasos de pre termalizacion

import numpy as np
import matplotlib.pyplot as plt

path = "/home/nunger/Documents/ising/res/"

energia = np.loadtxt(path + "tp2_energia_n256_sinB.txt")
mag = np.loadtxt(path + "tp2_mag_3.txt")
var_e = np.loadtxt(path + "tp2_varene_3.txt")
var_m = np.loadtxt(path + "tp2_varmag.txt")
temp = np.loadtxt(path + "tp2_temp_260.txt")

plt.style.use('seaborn-whitegrid')
plt.grid(b=True, which='mayor',color='k', linestyle='-')

#==============================================================================
plt.plot(temp,energia,"b.")
plt.title("Energia vs temperatura")
plt.ylabel('Energia media por sitio')
#==============================================================================

#==============================================================================
#plt.plot(temp,var_e, 'b.')
#plt.title('Calor especifico vs temperatura')
#plt.ylabel(r'Calor especifico por sitio $(C_V)$')
#==============================================================================


#plt.plot(temp,var_m, 'b.')
#plt.title('Susceptibilidad vs temperatura')
#plt.ylabel(r'Susceptibilidad por sitio $(\chi)$')
plt.xlabel('Temperatura (' + r'$T$' + ' )')

print temp[np.argmax(var_e)]
print temp[np.argmax(var_m)]
#print max(var_m)
#plt.plot(temp,mag,"r.")

plt.show()
