alias python3="/home/tversted/miniconda3/bin/python"
tmp_dir=/home/tversted/tmp
make_dir=cmake-build-release-odin

#tmp_dir=/tmp
#make_dir=cmake-build-materecclesia

name=tsallis

rounds=100000
#rounds=10000
averages=25
delta=0.9

run_experiment() {
      header=$tmp_dir/header_$name$1

      out=$tmp_dir/$name$1.out
      plt_out=$tmp_dir/$name$1.png

      out_mod2=$tmp_dir/mod2_$name$1.out
      plt_out_mod2=$tmp_dir/mod2_$name$1.png


      rm $header $out $plt_out $out_mod2 $plt_out_mod2 2> /dev/null
      rm $tmp_dir/*header* 2> /dev/null
      rm $tmp_dir/*.out* 2> /dev/null

      echo "runner,dataset,gap,k,rounds,averages,delta,output_path" >> $header
      echo "fpl_tsallis,stochastically_constrained_adversarial,3.2,$1,$rounds,$averages,$delta,$out" >> $header
      echo "fpl_tsallis,mod2,3.2,$1,$rounds,$averages,$delta,$out_mod2" >> $header

      ./$make_dir/efficient_multi_armed_bandits $header
      python3 plotting/plot_exp3_tsallis.py $out $plt_out
      python3 plotting/plot_exp3_tsallis.py $out_mod2 $plt_out_mod2

}

#for k in 4 8 16 32 128 256
for k in 4 8 16 32
#for k in 16
do
    run_experiment $k
done