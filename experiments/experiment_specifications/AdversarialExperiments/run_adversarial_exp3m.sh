#alias python3="/home/tversted/miniconda3/bin/python"
alias python3="/usr/bin/python3"
#make_dir=cmake-build-odin

tmp_dir=/mnt/ssd/bandits
#tmp_dir=../tmp
make_dir=cmake-build-heroicis

name=exp3m

rounds=10000
#rounds=10000
averages=100
delta=0.9

run_experiment() {
  for K in 2 4 8 16 30
  do
      header=$tmp_dir/header_$name$1

      out=$tmp_dir/$name$1_m$K.out
      plt_out=$tmp_dir/$name$1_m$K.png

      out_mod2=$tmp_dir/mod2_$name$1.out
      plt_out_mod2=$tmp_dir/mod2_$name$1.png

      out_stochastic=$tmp_dir/stochastic_$name$1.out
      plt_out_stochastic=$tmp_dir/stochastic_$name$1.png


      rm $header $out $plt_out $out_mod2 $plt_out_mod2 out_stochastic plt_out_stochastic 2> /dev/null

      echo "runner,dataset,gap,k,K,rounds,averages,delta,output_path" >> $header
      echo "adversarial_exp3m,stochastically_constrained_adversarial,3.2,$1,$K,$rounds,$averages,$delta,$out" >> $header
      echo "adversarial_exp3m,mod2,3.2,$1,$K,$rounds,$averages,$delta,$out_mod2" >> $header


      ./$make_dir/efficient_multi_armed_bandits $header
      python3 plotting/plot_adversarial_exp3m.py $out $plt_out
      python3 plotting/plot_adversarial_exp3m.py $out_mod2 $plt_out_mod2
      done

}

for k in 32 128 256 512
  do
    run_experiment $k
done
zip $tmp_dir/$name.zip $tmp_dir/*.out
rm $tmp_dir/*header* 2> /dev/null
rm $tmp_dir/*.out* 2> /dev/null