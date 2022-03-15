import pandas as pd
import matplotlib.pyplot as plt
import sys

plt.rcParams["figure.figsize"] = [7.50, 3.50]
plt.rcParams["figure.autolayout"] = True

headers = ['eta','mean_regret_exp3_T_half','std_regret_exp3_T_half','mean_regret_exp3_T','std_regret_exp3_T','mean_regret_exp3IX_T_half','std_regret_exp3IX_T_half','mean_regret_exp3IX_T','std_regret_exp3IX_T']

df = pd.read_csv(sys.argv[1], names=headers, skiprows=2)

fig, ax = plt.subplots()
ax = df.plot(ax=ax, kind='line', x='eta', y='mean_regret_exp3_T_half', label='mean_regret_exp3_T_half')

plt.legend(loc='best')
plt.show()