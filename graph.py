#!/usr/bin/env python
import numpy as np
import matplotlib.mlab as mlab
import matplotlib.pyplot as plt
import sys
    
x = []

for line in sys.stdin:
        if line == "" or line == "\n":
                break
        x.append(int(line))

print(x)
# the histogram of the data
n, bins, patches = plt.hist(x, 50)

plt.xlabel('Value')
plt.ylabel('Frequency')
plt.title(r'$\mathrm{Histogram}')
plt.axis([min(x), max(x), 0, 1000])
plt.grid(True)

plt.show()
