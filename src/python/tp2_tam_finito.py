import numpy as np
import matplotlib.pyplot as plt

path = "/home/nunger/Documents/ising/res/"

#n=1024
#lattice = np.loadtxt(path + "tp2_lattice_n1024.txt")

#data = np.zeros((1024,1024))
#for k in range(1024**2):
#    i = k/n
#    j = k%n
#    data[i,j] = lattice[k]



energia = np.loadtxt(path + "tp2_energia_n512.txt")

mag32 = np.loadtxt(path + "tp2_mag_n32.txt")
mag64 = np.loadtxt(path + "tp2_mag_n64.txt")
mag128 = np.loadtxt(path + "tp2_mag_n128.txt")
mag256 = np.loadtxt(path + "tp2_mag_n256.txt")
mag512 = np.loadtxt(path + "tp2_mag_n512.txt")
mag1024 = np.loadtxt(path + "tp2_mag_n1024.txt")

var_m32 = np.loadtxt(path + "tp2_varmag_n32.txt")
var_m64 = np.loadtxt(path + "tp2_varmag_n64.txt")
var_m128 = np.loadtxt(path + "tp2_varmag_n128.txt")
var_m256 = np.loadtxt(path + "tp2_varmag_n256.txt")
var_m512 = np.loadtxt(path + "tp2_varmag_n512.txt")
var_m1024 = np.loadtxt(path + "tp2_varmag_n1024.txt")

var_e32 = np.loadtxt(path + "tp2_varene_n32.txt")
var_e64 = np.loadtxt(path + "tp2_varene_n64.txt")
var_e128 = np.loadtxt(path + "tp2_varene_n128.txt")
var_e256 = np.loadtxt(path + "tp2_varene_n256.txt")
var_e512 = np.loadtxt(path + "tp2_varene_n512.txt")
var_e1024 = np.loadtxt(path + "tp2_varene_n1024.txt")

temp = np.loadtxt(path + "tp2_temp_260.txt")

plt.style.use('seaborn-whitegrid')
plt.grid(b=True, which='mayor',color='k', linestyle='-')

plt.figure(0)
plt.plot(temp,mag32,"c.")
plt.plot(temp,mag64,"b.")
plt.plot(temp,mag128,"r.")
plt.plot(temp,mag256,"m.")
plt.plot(temp,mag512,"k.")
plt.plot(temp,mag1024,"g.")
plt.title("Magnetizacion")

plt.figure(1)
plt.plot(temp,var_e32,"c.", label='L=32')
plt.plot(temp,var_e64,"b.", label='L=64')
plt.plot(temp,var_e128,"r.", label='L=128')
plt.plot(temp,var_e256,"m.", label='L=256')
plt.plot(temp,var_e512,"k.", label='L=512')
plt.plot(temp,var_e1024,"g.", label='L=1024')

plt.xlabel(r'Temperatura $(T)$')
plt.ylabel(r'Calor especifico $(C_V)$')
plt.legend(loc=1)

plt.show()
