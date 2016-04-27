#!/usr/bin/env python
import numpy as np
import matplotlib
matplotlib.use('GTK')
import matplotlib.pyplot as plt
import sys
import re

ns = []
stimes = []
ptimes = []

for line in sys.stdin:
        if line == "" or line == "\n":
                break
        elif line =="BEGIN" or line == "END":
                continue
        elif line.startswith("n is: "):
                line = re.sub("[^0-9\.]", "", line)
                ns.append(int(line))
        elif line.startswith("Parallel Radix time: "):
                line = re.sub("[^0-9\.]", "", line)
                ptimes.append(float(line))
        elif line.startswith("Serial Radix time: "):
                line = re.sub("[^0-9\.]", "", line)
                stimes.append(float(line))


plt.plot(ns, stimes, 'r.', ns, ptimes, 'b.')

plt.xlabel('Sample Size (100 Million)')
plt.ylabel('Execution Time (s)')
plt.yscale('log')
plt.title(r'$\mathrm{Execution Times in Serial and Parallel}')
plt.axis([min(ns), max(ns), 0, max([max(ptimes), max(stimes)])])
plt.grid(True)

plt.show()
