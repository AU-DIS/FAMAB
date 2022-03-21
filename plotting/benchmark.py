import sys
import matplotlib.pyplot as plt
import pandas as pd


styles = ['-', '--', '-.', ':', ',']
colours = ['b', 'g', 'r', 'c', 'm', 'y', 'k']

df = pd.read_csv(sys.argv[1])
algorithms = sorted(set(df["name"]))
plt.figure(0, figsize=(10, 5))
for nr, algo in enumerate(algorithms):
    rows = df.loc[df["name"] == algo]
    ks = [x for x in rows["k"]]
    runtimes = [x for i, x in enumerate(rows["cputime"])]
    values = range(len(ks))
    plt.plot(values[1:], runtimes[1:], styles[nr % len(styles)], color = colours[nr % len(colours)])
    plt.xticks(values[1:],ks[1:])
    plt.yscale('log')



plt.xlabel('K')
plt.ylabel('cputime')
plt.legend(algorithms)
plt.grid(True)
if len(sys.argv) >= 3:
    plt.savefig(sys.argv[2])
else:
    plt.show()






