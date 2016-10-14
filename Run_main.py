# Runs main.cpp and plots the generated .txt files

import os

os.system('c++ main.cpp celestialbody.cpp euler.cpp solarsystem.cpp vec3.cpp -o main.o -O3 -I /usr/local/Cellar/armadillo/7.400.2/include -DARMA_DONT_USE_WRAPPER -lblas -llapack')
os.system('./main.o')

from math import *
import numpy as np
from matplotlib import pyplot as plt

def read_rho_wavefunctions(filename):
    infile = open(filename, 'r')
    # Elements to be read in file:
    rho = []; u1 = []; u2 = []; u3 = [];
    # Read lines except for the first one:
    lines = infile.readlines()[1:]
    for line in lines:
        words = line.split()
        rho.append(float(words[0]))
        u1.append(float(words[1]))
        u2.append(float(words[2]))
        u3.append(float(words[3]))
    infile.close()
    return rho, u1, u2, u3

# Fetching data by a call on read_x_u_v for three different n:
rho, u1, u2, u3 = read_rho_wavefunctions('earth.txt')

plt.scatter(u1,u2)

# Plotting commands to look at the wave functions:
#fig, ax = plt.subplots(1)
#ax.set_title('Wave function')
#ax.set_xlabel('$\\rho$')
#ax.set_ylabel('$\mid u(\\rho) \mid^2$')
#ax.plot(rho,u1,'r-',label='$\mid u_0(\\rho) \mid^2$')
#ax.plot(rho,u2,'b-',label='$\mid u_1(\\rho) \mid^2$')
#ax.legend(loc='upper right',fancybox='True')
#ax.grid()
plt.savefig('Earth.pdf')
