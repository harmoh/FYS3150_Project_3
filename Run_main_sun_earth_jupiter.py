# Runs main.cpp and plots the generated .txt files

import os

os.system('c++ main.cpp celestialbody.cpp euler.cpp solarsystem.cpp vec3.cpp verlet.cpp -o main.o -O3 -std=c++11')
os.system('./main.o 2') # Argument for choosing to run program for three-body system.

from math import *
import numpy as np
from matplotlib import pyplot as plt

def read(filename):
    infile = open(filename, 'r')
    # Elements to be read in file:
    x1 = []; y1 = []; x2 = []; y2 = []; x3 = []; y3 = [];
    # Read lines except for the first one:
    lines = infile.readlines()[1:]
    for line in lines:
        words = line.split()
        x1.append(float(words[0]))
        y1.append(float(words[1]))
        x2.append(float(words[3]))
        y2.append(float(words[4]))
        x3.append(float(words[6]))
        y3.append(float(words[7]))
    infile.close()
    return x1, y1, x2, y2, x3, y3

# Fetching data by a call on read_x_u_v for three different n:
x1, y1, x2, y2, x3, y3 = read('Positions.txt')

plt.xlabel('x in AU')
plt.ylabel('y in AU')
plt.rcParams.update({'font.size': 10})
plt.plot(x1, y1, 'r-', linewidth = 1.0, label = 'Sun')
plt.plot(x2, y2, 'b-', linewidth = 0.5, label = 'Earth')
plt.plot(x3, y3, 'g-', linewidth = 1.0, label = 'Jupiter')
plt.legend(loc='upper right',fancybox='True')
plt.grid()

plt.savefig('SunEarthJupiter.eps', format = 'eps', dpi = 1000, bbox_inches='tight')
