# Programa para testear pasos de pre termalizacion

import numpy as np
import matplotlib.pyplot as plt

path = "/home/nunger/Documents/ising/res/"

energia = np.loadtxt(path + "tp2_energia.txt")
mag = np.loadtxt(path + "tp2_mag.txt")
var_e = np.loadtxt(path + "tp2_varene.txt")
var_m = np.loadtxt(path + "tp2_varmag.txt")
temp = np.loadtxt(path + "tp2_temp_260.txt")

plt.plot(temp,var_e,"b.")
plt.title("Calor especifico")

print temp[np.argmax(var_e)]
print temp[np.argmax(var_m)]
#print max(var_m)
#plt.plot(temp,mag,"r.")
