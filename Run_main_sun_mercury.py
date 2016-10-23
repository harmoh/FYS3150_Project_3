# Runs main.cpp and plots the generated .txt files

import os

os.system('c++ main.cpp celestialbody.cpp euler.cpp solarsystem.cpp vec3.cpp verlet.cpp -o main.o -O3 -std=c++11')
os.system('./main.o 4') # Argument for choosing only sun and earth in the system.

from math import *
import numpy as np
from matplotlib import pyplot as plt

def read(filename):
    infile = open(filename, 'r')
    # Elements to be read in file:
    x = []; y = [];
    # Read lines except for the first one:
    lines = infile.readlines()[1:]
    for line in lines:
        words = line.split()
        x.append(float(words[0]))
        y.append(float(words[1]))
    infile.close()
    return x, y,

# Fetching data by a call on read_x_u_v for three different n:
x, y = read('PerihelionAngle.txt')

plt.xlabel('Years')
plt.ylabel('Perhelion angle in arc seconds')
plt.rcParams.update({'font.size': 10})
plt.plot(x, y)
plt.grid()

plt.savefig('PerihelionAngle.eps', format = 'eps', dpi = 1000, bbox_inches='tight')
