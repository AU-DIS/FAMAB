import pandas as pd
import matplotlib.pyplot as plt
import sys

plt.rcParams["figure.figsize"] = [7.50, 3.50]
plt.rcParams["figure.autolayout"] = True

headers = ['eta','mean_regret_exp3_T_half','std_regret_exp3_T_half','mean_regret_exp3_T','std_regret_exp3_T','mean_regret_exp3IX_T_half','std_regret_exp3IX_T_half','mean_regret_exp3IX_T','std_regret_exp3IX_T']

df = pd.read_csv(sys.argv[1], names=headers, skiprows=2)

# plot lines
fig = plt.figure()
ax = fig.add_subplot()
plt.errorbar(df.loc[:,'eta'], df.loc[:,'mean_regret_exp3_T_half'], df.loc[:,'std_regret_exp3_T_half'], label = "mean regret Exp3")
plt.errorbar(df.loc[:,'eta'], df.loc[:,'mean_regret_exp3IX_T_half'], df.loc[:,'std_regret_exp3IX_T_half'], label = "mean regret Exp3IX")
ax.set_xscale('log')
ax.legend()
plt.show()