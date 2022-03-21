alias python3="/home/tversted/miniconda3/bin/python"

tmp_dir=/home/tversted/tmp
name=tsallis
make_dir=cmake-build-release-odin
rounds=100000
#rounds=1000
averages=1

run_experiment() {
      header=$tmp_dir/header_$name$1
      out=$tmp_dir/$name$1.out
      plt_out=$tmp_dir/$name$1.png
      rm $header $out $plt_out 2> /dev/null
      rm $tmp_dir/*header* 2> /dev/null
      rm $tmp_dir/*.out* 2> /dev/null

      echo "runner,dataset,gap,k,rounds,averages,output_path" >> $header
      echo "tsallis,stochastically_constrained_adversarial,1.6,$1,$rounds,$averages,$out" >> $header

      ./$make_dir/efficient_multi_armed_bandits $header
      python3 plotting/plot_tsallis.py $out $plt_out
}


for k in 2 8 32 128
do
    run_experiment $k & disown
done