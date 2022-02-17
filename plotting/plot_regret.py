import sys
import matplotlib.pyplot as plt
import numpy as np
from matplotlib import colors

with open(sys.argv[1], 'r') as f:
    max_regret = float(f.readline())
    lines = f.readlines()[0].replace('\n', '').split(',')

lines = np.array([float(x) for x in lines])
lines = np.cumsum(lines)

N = len(lines)
for i in range(N):
    if i > 1:
        pass
        #lines[i] /= i
m = np.min(lines)
lines = [x - m for x in lines]

plt.plot(range(len(lines)), lines)
#plt.ylim(min(lines), max_regret)
plt.show()
#plt.savefig(sys.argv[2])




