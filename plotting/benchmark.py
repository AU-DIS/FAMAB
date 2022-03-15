import sys
import matplotlib.pyplot as plt
import pandas as pd

df = pd.read_csv(sys.argv[1])
algorithms = set(df["name"])

for algo in algorithms:
    rows = df.loc[df["name"] == algo]
    ks = [x for x in rows["k"]]
    runtimes = [x/ks[i] for i, x in enumerate(rows["cputime"])]
    values = range(len(ks))
    plt.plot(values[1:], runtimes[1:])
    plt.xticks(values[1:],ks[1:])



plt.xlabel('K')
plt.ylabel('cputime / K')
plt.legend(algorithms)
plt.grid(True)
if len(sys.argv) >= 3:
    plt.savefig(sys.argv[2])
else:
    plt.show()






