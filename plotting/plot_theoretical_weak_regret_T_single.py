import pandas as pd
import matplotlib.pyplot as plt
import sys

plt.rcParams["figure.figsize"] = [4, 4]
plt.rcParams["figure.autolayout"] = True

df = pd.read_csv(sys.argv[1], skiprows=1)

# plot lines
fig1 = plt.figure()
ax1 = fig1.add_subplot()
ax1.scatter(df['T'], df['average_divided_by_promise'], s=30)
ax1.set_xlabel('T')
ax1.set_xscale('log')
ax1.set_ylabel('weak regret / expected regret bound')
ax1.set_title(f"Exp3.M regret plot for m=10, k=100")

plt.show()