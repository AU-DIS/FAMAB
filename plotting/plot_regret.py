import sys
import matplotlib.pyplot as plt
import numpy as np
import numpy as np
from sklearn.linear_model import LinearRegression
from matplotlib import colors
model = LinearRegression()

with open(sys.argv[1], 'r') as f:
    mean_value = float(f.readline())
    lines = f.readlines()[0].replace('\n', '').split(',')


lines = np.array([float(x) for x in lines])
max_val = np.max(lines)
lines = np.cumsum(lines)

x = range(len(lines))
baseline = [mean_value * (i+1) for i, x in enumerate(x)]
y = lines
#model.fit(x, y)
plt.plot(x, y)
plt.plot(x, baseline)
plt.ylim(0, len(lines))
plt.show()
#plt.savefig(sys.argv[2])




