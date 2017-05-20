# Programa para testear pasos de pre termalizacion

import numpy as np
import matplotlib.pyplot as plt

path = "/home/nunger/Documents/ising/res/"

energia = np.loadtxt(path + "tp2_pterm_e_4000.txt")
#energia_p = np.loadtxt(path + "tp2_pterm_ep_20000.txt")

plt.plot(energia, "b.")
#plt.plot(energia_p, "r.")
plt.show()
