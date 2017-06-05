import numpy as np
import matplotlib.pyplot as plt

path = "/home/nunger/Documents/ising/res/"

energia = np.loadtxt(path + "tp2_energia_n512.txt")
mag = np.loadtxt(path + "tp2_mag_n8.txt")
var_e = np.loadtxt(path + "tp2_varene_n64.txt")
var_m = np.loadtxt(path + "tp2_varmag_n64.txt")
temp = np.loadtxt(path + "tp2_temp_260.txt")

plt.plot(temp,mag,"b.")
plt.title("Magnetizacion")
plt.show()
