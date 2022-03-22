import sys
import matplotlib.pyplot as plt
import numpy as np
from matplotlib import colors
import itertools

regrets = {}
styles = ['o', 'v', '^', '<', '>', 's', '8', 'p']


with open(sys.argv[1], 'r') as f:
    metadata = f.readline().replace('"', '').replace('\n', '').split(',')
    algorithms = metadata[4:]
    algorithms = [x for x in algorithms if x != '']
    for algorithm in algorithms:
        if algorithm != '':
            regrets[algorithm] = f.readline().replace('\n', '').split(',')

description = metadata[0]
k = metadata[1]
rounds = metadata[2]
gap = float(metadata[3])


colormap = {
    "Exp3": "forestgreen",
    "Exp3.1": "limegreen",
    "UCB1 (Exp3)": "lime",
    "FPL": "darkorchid",
    "UCB (FPL)": "magenta",
    "Tsallis-INF (IW)": "royalblue",
    "Tsallis-INF (RV)": "cornflowerblue",
    "Uniform": "red"
}

ys = []
algorithms = sorted(algorithms)
fig, ax = plt.subplots(2, figsize=(10, 10))
legends = [[], []]

#"Exp3",
#"Exp3.1",
#"UCB1 (Exp3)",
#"FPL",
#"UCB (FPL)",
#"Tsallis-INF (IW)",
#"Tsallis-INF (RV)",
#"Uniform"

for nr, algorithm in enumerate(algorithms):
    lines = np.array([float(x) for x in regrets[algorithm]])
    max_val = np.max(lines)
    lines = np.cumsum(lines)
    ys.append(lines)
    x = range(len(lines))
    y = lines

    if "Uniform" in algorithm or "Exp3" in algorithm:
        legends[0].append(algorithm)
        ax[0].plot(x, y, color=colormap[algorithm])
    if "Uniform" in algorithm or "Tsallis" in algorithm or "FPL" in algorithm:
        legends[1].append(algorithm)
        ax[1].plot(x, y, color=colormap[algorithm])

gap_xs = []
gap_ys = []
gap_iter = 0
while int(gap**gap_iter) <= int(rounds):
    gap_xs.append(int(gap**gap_iter))
    gap_iter += 1
print(gap_xs)

ax[0].vlines(gap_xs, ymin=np.min([np.min(obs) for obs in ys]), ymax=np.max([np.max(obs) for obs in ys]))
ax[1].vlines(gap_xs, ymin=np.min([np.min(obs) for obs in ys]), ymax=np.max([np.max(obs) for obs in ys]))

ax[0].set_title(f"{description} k = {k}")
ax[0].set_xlabel('Rounds')
ax[0].set_ylabel('Cumulative regret')
ax[1].set_title(f"{description} k = {k}")
ax[1].set_xlabel('Rounds')
ax[1].set_ylabel('Cumulative regret')

ax[0].grid(True)
ax[1].grid(True)
#plt.title(f"{description} k = {k}")
#plt.xlabel('Rounds')
#plt.ylabel('Cumulative regret')

#plt.title(f"{description} k = {k}")
#plt.ylim([0, int(rounds)])
ax[0].legend(legends[0])
ax[1].legend(legends[1])

if len(sys.argv) >= 3:
    plt.savefig(sys.argv[2])
else:
    plt.show()


