alias python3="/home/tversted/miniconda3/bin/python"
tmp_dir=/home/tversted/tmp
make_dir=cmake-build-release-odin

#tmp_dir=/tmp
#make_dir=cmake-build-materecclesia

name=tsallis

#rounds=10000
rounds=100000
averages=100
delta=0.9

run_experiment() {
  for K in 2 4 8 16 30
  do
      header=$tmp_dir/header_$name$1$K

      out=$tmp_dir/$name$1$K.out
      plt_out=$tmp_dir/$name$1$K.png

      out_mod2=$tmp_dir/mod2_$name$1$K.out
      plt_out_mod2=$tmp_dir/mod2_$name$1$K.png


      rm $header $out $plt_out 2> /dev/null
      rm $tmp_dir/*header* 2> /dev/null
      rm $tmp_dir/*.out* 2> /dev/null

      echo "runner,dataset,gap,k,K,rounds,averages,delta,output_path" >> $tmp_dir/header_$name$1$K
      echo "tsallis_exp3m,stochastically_constrained_adversarial,3.2,$1,$K,$rounds,$averages,$delta,$out" >> $tmp_dir/header_$name$1$K
      echo "tsallis_exp3m,mod2,3.2,$1,$K,$rounds,$averages,$delta,$out_mod2" >> $tmp_dir/header_$name$1$K


      ./$make_dir/efficient_multi_armed_bandits $header
      python3 plotting/plot_tsallis_exp3m.py $out $plt_out
      python3 plotting/plot_tsallis_exp3m.py $out_mod2 $plt_out_mod2
      done

}

for k in 32 128 256 512
  do
    run_experiment $k
done