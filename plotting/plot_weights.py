import sys
import matplotlib.pyplot as plt
import numpy as np
from matplotlib import colors

lines = []
with open(sys.argv[1], 'r') as f:
    lines = f.readlines()[0].replace('\n', '').split(',')

lines = np.array([float(x) for x in lines])
plt.scatter(range(len(lines)), lines)
plt.show()
plt.savefig(sys.argv[2])




