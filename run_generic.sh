./cmake-build-materecclesia/efficient_multi_armed_bandits experiments/experiment_specifications/generic.csv
alias python3="/opt/homebrew/bin/python3"
python3 plotting/plot_regret.py /tmp/genericout1 /tmp/genericout1.png
python3 plotting/plot_regret.py /tmp/genericout2 /tmp/genericout2.png
python3 plotting/plot_regret.py /tmp/genericout3 /tmp/genericout3.png
python3 plotting/plot_regret.py /tmp/genericout4 /tmp/genericout4.png
python3 plotting/plot_regret.py /tmp/genericout5 /tmp/genericout5.png

