import numpy as np
import matplotlib.pyplot as plt

path = "/home/nunger/Documents/ising/res/"

energia = np.loadtxt(path + "tp2_energia_aferro.txt")
mag = np.loadtxt(path + "tp2_mag_aferro.txt")
var_e = np.loadtxt(path + "tp2_varene_aferro.txt")
var_m = np.loadtxt(path + "tp2_varmag_aferro.txt")
temp = np.loadtxt(path + "tp2_temp_260.txt")

plt.plot(temp, mag, 'b.')
plt.show()
