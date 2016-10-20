# Runs main.cpp and plots the generated .txt files

import os

os.system('c++ main.cpp celestialbody.cpp euler.cpp solarsystem.cpp vec3.cpp verlet.cpp -o main.o -O3 -std=c++11')
os.system('./main.o 3') # Argument for calculating system for all planets (including Pluto)

from math import *
import numpy as np
from matplotlib import pyplot as plt

def read(filename):
    infile = open(filename, 'r')
    # Elements to be read in file:
    x1 = []; y1 = []; x2 = []; y2 = []; x3 = []; y3 = []; x4 = []; y4 = []; x5 = []; y5 = []; x6 = []; y6 = []; x7 = []; y7 = []; x8 = []; y8 = []; x9 = []; y9 = []; x10 = []; y10 = [];
    # Read lines except for the first one:
    lines = infile.readlines()[1:]
    for line in lines:
        words = line.split()
        x1.append(float(words[0]))
        y1.append(float(words[1]))
        x2.append(float(words[2]))
        y2.append(float(words[3]))
        x3.append(float(words[4]))
        y3.append(float(words[5]))
        x4.append(float(words[6]))
        y4.append(float(words[7]))
        x5.append(float(words[8]))
        y5.append(float(words[9]))
        x6.append(float(words[10]))
        y6.append(float(words[11]))
        x7.append(float(words[12]))
        y7.append(float(words[13]))
        x8.append(float(words[14]))
        y8.append(float(words[15]))
        x9.append(float(words[16]))
        y9.append(float(words[17]))
        x10.append(float(words[18]))
        y10.append(float(words[19]))
    infile.close()
    return x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, x6, y6, x7, y7, x8, y8, x9, y9, x10, y10

# Fetching data by a call on read_x_u_v for three different n:
x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, x6, y6, x7, y7, x8, y8, x9, y9, x10, y10 = read('positions.txt')

plt.xlabel('x in AU')
plt.ylabel('y in AU')
plt.rcParams.update({'font.size': 10})
#plt.axis([-40, 60, -40, 50])
plt.plot(x1, y1, 'r-', linewidth = 0.1, label = 'Sun')
plt.plot(x2, y2, 'm-', linewidth = 0.1, label = 'Mercury')
plt.plot(x3, y3, 'c-', linewidth = 0.5, label = 'Venus')
plt.plot(x4, y4, 'b-', linewidth = 0.5, label = 'Earth')
plt.plot(x5, y5, 'r-', linewidth = 0.5, label = 'Mars')
plt.plot(x6, y6, 'g-', linewidth = 0.5, label = 'Jupiter')
plt.plot(x7, y7, 'y-', linewidth = 1.0, label = 'Saturn')
plt.plot(x8, y8, 'c-', linewidth = 1.0, label = 'Uranus')
plt.plot(x9, y9, 'b-', linewidth = 1.0, label = 'Neptune')
plt.plot(x10, y10, 'k-', linewidth = 1.0, label = 'Pluto')
plt.legend(loc='upper right',fancybox='True')
plt.grid()

plt.savefig('SolarSystem.eps', format = 'eps', dpi = 1000, bbox_inches='tight')
