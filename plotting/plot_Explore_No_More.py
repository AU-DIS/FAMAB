import pandas as pd
import matplotlib.pyplot as plt
import sys

plt.rcParams["figure.figsize"] = [7.50, 3.50]
plt.rcParams["figure.autolayout"] = True

headers = ['eta','mean_regret_exp3_T_half','std_regret_exp3_T_half','mean_regret_exp3_T','std_regret_exp3_T','mean_regret_exp3IX_T_half','std_regret_exp3IX_T_half','mean_regret_exp3IX_T','std_regret_exp3IX_T']

df = pd.read_csv(sys.argv[1], skiprows=1)

# plot lines
fig = plt.figure()
ax = fig.add_subplot()
ax.errorbar(df.loc[:,'eta'], df.loc[:,'mean_regret_exp3_T'], df.loc[:,'std_regret_exp3_T'], label = "mean regret Exp3")
ax.errorbar(df.loc[:,'eta'], df.loc[:,'mean_regret_exp3IX_T'], df.loc[:,'std_regret_exp3IX_T'], label = "mean regret Exp3IX")
ax.set_xscale('log')
ax.legend()
plt.show()