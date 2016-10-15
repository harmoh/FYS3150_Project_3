# Runs main.cpp and plots the generated .txt files

import os

os.system('c++ main.cpp celestialbody.cpp euler.cpp solarsystem.cpp vec3.cpp verlet.cpp -o main.o -O3 -I /usr/local/Cellar/armadillo/7.400.2/include -DARMA_DONT_USE_WRAPPER -lblas -llapack')
os.system('./main.o')

from math import *
import numpy as np
from matplotlib import pyplot as plt

def read_rho_wavefunctions(filename):
    infile = open(filename, 'r')
    # Elements to be read in file:
    x1 = []; y1 = []; x2 = []; y2 = [];
    # Read lines except for the first one:
    lines = infile.readlines()[1:]
    for line in lines:
        words = line.split()
        x1.append(float(words[0]))
        y1.append(float(words[1]))
        x2.append(float(words[3]))
        y2.append(float(words[4]))
    infile.close()
    return x1, y1, x2, y2

# Fetching data by a call on read_x_u_v for three different n:
x1, y1, x2, y2 = read_rho_wavefunctions('positions.txt')

plt.plot(x1, y1, 'r-', linewidth = 1.0)
plt.plot(x2, y2, 'b-', linewidth = 1.0)

plt.savefig('SunEarth.eps', format = 'eps', dpi = 10000)
