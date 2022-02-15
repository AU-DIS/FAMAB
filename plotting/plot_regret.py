import sys
import matplotlib.pyplot as plt
import numpy as np
from matplotlib import colors

lines = []
with open(sys.argv[1], 'r') as f:
    lines = f.readlines()[0].replace('\n', '').split(',')

lines = np.array([float(x) for x in lines])
lines = np.cumsum(lines)
N = len(lines)
lines = np.array([x/(i+1) for i, x in enumerate(lines[1::])])
lines = lines[5:]
plt.plot(range(len(lines)), lines)
#plt.ylim(0, 5)
plt.show()
#plt.savefig(sys.argv[2])




