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
    x = []; y = []; y = [];
    # Read lines except for the first one:
    lines = infile.readlines()[1:]
    for line in lines:
        words = line.split()
        x.append(float(words[0]))
        y.append(float(words[1]))
    infile.close()
    return x, y

# Fetching data by a call on read_x_u_v for three different n:
x, y = read_rho_wavefunctions('earth.txt')

plt.plot(x, y, '-')

plt.savefig('Earth.pdf')
