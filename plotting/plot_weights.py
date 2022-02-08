import sys
import matplotlib.pyplot as plt
from matplotlib import colors

lines = []
with open(sys.argv[1], 'r') as f:
    lines = f.readlines()[0].replace('\n', '').split(',')
plt.scatter(range(len(lines)), lines)

plt.savefig(sys.argv[2])




