import sys
import matplotlib.pyplot as plt
import pandas as pd


styles = ['-', '--', '-.', ':', ',']
colours = ['b', 'g', 'r', 'c', 'm', 'y', 'k']

df = pd.read_csv(sys.argv[1])
algorithms = sorted(set(df["name"]))
print(algorithms)
ks = sorted(set(df['k']))
ks = [int(x) for x in ks]
plt.figure(0, figsize=(10, 5))

for nr, algo in enumerate(algorithms):
    rows = df.loc[df["name"] == algo]
    runtimes = [x for i, x in enumerate(rows["cpu_time"])]
    plt.loglog(ks, runtimes)
    #plt.xticks(values[1:],ks[1:])
    #plt.yscale('log')
    #plt.xscale('log')



plt.xlabel('k')
plt.ylabel('cputime')
plt.legend(algorithms)
plt.grid(True)
if len(sys.argv) >= 3:
    plt.savefig(sys.argv[2])
else:
    plt.show()






