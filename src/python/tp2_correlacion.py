#Correlaciones

import numpy as np
import matplotlib.pyplot as plt

path = "/home/nunger/Documents/ising/res/"

corr = np.loadtxt(path + "tp2_corr_e_t3.txt")

plt.plot(corr, "b.")
plt.show()
