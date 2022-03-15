import sys
import matplotlib.pyplot as plt
import numpy as np
import numpy as np
from sklearn.linear_model import LinearRegression
from matplotlib import colors
model = LinearRegression()

regrets = []

with open(sys.argv[1], 'r') as f:
    metadata = f.readline().replace('"', '').replace('\n', '').split(',')
    algorithms = metadata[4:]
    for _ in range(len(algorithms)):
        regrets.append(f.readline().replace('\n', '').split(','))

description = metadata[0]
k = metadata[1]
rounds = metadata[2]
expected_value = float(metadata[3])

indices = np.argsort(algorithms)
regrets = regrets[indices]
algorithms = algorithms[indices]

for lines in regrets:
    lines = np.array([float(x) for x in lines])
    max_val = np.max(lines)
    lines = np.cumsum(lines)
    x = range(len(lines))
    y = lines
    plt.plot(x, y)

plt.xlabel('Rounds')
plt.ylabel('Cumulative regret')
plt.grid(True)
plt.title(f"{description} with k = {k}")
plt.ylim(0, int(rounds))

plt.legend(algorithms)

if len(sys.argv) >= 3:
    plt.savefig(sys.argv[2])
else:
    plt.show()




