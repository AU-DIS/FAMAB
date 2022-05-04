#alias python3="/home/tversted/miniconda3/bin/python"
alias python3="/usr/bin/python3"
#make_dir=cmake-build-odin

tmp_dir=/mnt/ssd/bandits
#tmp_dir=../tmp
make_dir=cmake-build-heroicis

name=FPL

#rounds=1000
#rounds=1000
rounds=10000
averages=100
#averages=25
gap=3.2
delta=0.9

run_experiment() {
      header=$tmp_dir/header_$name$1

      out=$tmp_dir/$name$1.out
      plt_out=$tmp_dir/$name$1.png

      out_mod2=$tmp_dir/$name$1_mod2.out
      plt_out_mod2=$tmp_dir/$name$1_mod2.png

      out_stochastic=$tmp_dir/stochastic_$name$1.out
      plt_out_stochastic=$tmp_dir/stochastic_$name$1.png


      rm $header $out $plt_out $out_mod2 $plt_out_mod2 out_stochastic plt_out_stochastic 2> /dev/null


      echo "runner,dataset,gap,k,rounds,averages,delta,output_path" >> $header
      echo "fpl_adversarial,stochastically_constrained_adversarial,3.2,$1,$rounds,$averages,$delta,$out" >> $header
      echo "fpl_adversarial,mod2,3.2,$1,$rounds,$averages,$delta,$out_mod2" >> $header
      #echo "fpl_adversarial,stochastic,3.2,$1,$rounds,$averages,$delta,$out_stochastic" >> $header

      ./$make_dir/efficient_multi_armed_bandits $header
      python3 plotting/plot_compare.py $out $plt_out
      python3 plotting/plot_compare.py $out_mod2 $plt_out_mod2
      #python3 plotting/plot_compare.py $out_stochastic $plt_out_stochastic

}

for k in 16 32 64 128
#for k in 16 32 64 128
#for k in 16384
#for k in 1024 2048 4096 8192 16384
do
    run_experiment $k
done
zip $tmp_dir/$name.zip $tmp_dir/*.out
rm $tmp_dir/*header* 2> /dev/null
rm $tmp_dir/*.out* 2> /dev/null
