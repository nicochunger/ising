import numpy as np
import matplotlib.pyplot as plt

path = "/home/nunger/Documents/ising/res/"

mag_237 = np.loadtxt(path + "tp2_mag_t237.txt")

mag_237 = mag_237 / (32*32)

hist_mag = np.histogram(mag_237, bins=30)

plt.figure(0)
plt.bar(hist_mag[1][:-1], hist_mag[0],width=0.01)

plt.figure(1)
plt.plot(mag_237)
plt.show()