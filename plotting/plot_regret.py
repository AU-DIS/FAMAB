import sys
import matplotlib.pyplot as plt
import numpy as np
from matplotlib import colors

with open(sys.argv[1], 'r') as f:
    max_regret = float(f.readline())
    lines = f.readlines()[0].replace('\n', '').split(',')


lines = np.array([float(x) for x in lines])
max_val = max(lines)
lines = np.array([x/max_val for x in lines])

lines = np.cumsum(lines)
N = len(lines)
for i in range(N):
    if i > 0:
        #pass
        lines[i] /= i

#print([(i, x) for i, x in enumerate(lines) if x >= 2])

plt.plot(range(len(lines)), lines)
plt.ylim(0, 1)
plt.show()
#plt.savefig(sys.argv[2])




