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

plt.plot(corr1, "b.")
plt.plot(corr2, "y.")
plt.plot(corr3, "g.")
plt.plot(corr4, "m.")
plt.plot(corr5, "c.")
plt.plot(corr6, "r.")
plt.show()
