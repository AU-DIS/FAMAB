#alias python3="/home/tversted/miniconda3/bin/python"
#alias python3="/opt/homebrew/bin/python3"
alias python3="$(which python3)"
#"/usr/bin/python3"


make_dir=cmake-build-release-wsl
tmp_dir=/tmp
if [[ $make_dir == cmake-build-release-odin ]]; then
  mkdir -p /home/$(whoami)/tmp
  tmp_dir=/home/$(whoami)/tmp
fi


name=exp3m

rounds=10000
averages=100
delta=0.9

run_experiment() {
  for m in 2
  do

      echo $1
      echo $m
      header=$tmp_dir/header_$name$1_$m

      out=$tmp_dir/constrained_$name$1_$m.out
      plt_out=$tmp_dir/constrained_$name$1_$m.png

      out_mod2=$tmp_dir/mod2_$name$1_$m.out
      plt_out_mod2=$tmp_dir/mod2_$name$1_$m.png

      out_stoca=$tmp_dir/stoca_$name$1_$m.out
      plt_out_stoca=$tmp_dir/stoca_$name$1_$m.png

      rm -f $header $out $plt_out 2> /dev/null
      rm -f $tmp_dir/*header* 2> /dev/null
      rm -f $tmp_dir/*.out* 2> /dev/null

      echo "runner,dataset,gap,k,m,rounds,averages,delta,output_path" >> $header
      echo "adversarial_exp3m,stochastically_constrained_adversarial,3.2,$1,$m,$rounds,$averages,$delta,$out" >> $header
      echo "adversarial_exp3m,mod2,3.2,$1,$m,$rounds,$averages,$delta,$out_mod2" >> $header
      echo "adversarial_exp3m,stochastic,3.2,$1,$m,$rounds,$averages,$delta,$out_stoca" >> $header

      ./$make_dir/efficient_multi_armed_bandits $header

      python3 plotting/plot_adversarial_exp3m.py $out $plt_out
      python3 plotting/plot_adversarial_exp3m.py $out_mod2 $plt_out_mod2
      python3 plotting/plot_adversarial_exp3m.py $out_stoca $plt_out_stoca
      done
}

for k in 2000
  do
    run_experiment $k
done
zip $tmp_dir/$name.zip $tmp_dir/*.out
rm $tmp_dir/*header* 2> /dev/null
rm $tmp_dir/*.out* 2> /dev/null