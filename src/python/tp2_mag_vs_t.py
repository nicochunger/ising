# Programa que grafica la magnetizacion en funcion de la temperatura

import numpy as np
import matplotlib.pyplot as plt

path = "/home/nunger/Documents/ising/res/"

mag0 = np.loadtxt(path + "tp2_mag.txt")
mag1 = np.loadtxt(path + "tp2_mag_1.txt")
mag2 = np.loadtxt(path + "tp2_mag_2.txt")
mag3 = np.loadtxt(path + "tp2_mag_3.txt")
temp = np.loadtxt(path + "tp2_temp_260.txt")

plt.plot(temp, abs(mag0), 'b.')
plt.plot(temp, abs(mag1), 'r.')
plt.plot(temp, abs(mag2), 'g.')
plt.plot(temp, abs(mag3), 'y.')
plt.show()

