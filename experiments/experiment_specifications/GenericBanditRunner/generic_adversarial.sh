alias python3="/home/tversted/miniconda3/bin/python"
#alias python3="/opt/homebrew/bin/python3"

tmp_dir=/home/tversted/tmp
name=adversarial
make_dir=cmake-build-release-odin

run_experiment() {
    n=10
    m=$1
    averages=40
    for ((j=1, pow=n; j<m; j++)); do ((pow *= n)); done

    for K in 10 100 100
    do
      header=$tmp_dir/header_$name$1_$K
      out=$tmp_dir/$name$1.out_$K
      plt_out=$tmp_dir/$name$1_$K.png
      rm $header $out $plt_out 2> /dev/null

      echo "runner,K,rounds,averages,dataset,output_path" >> $header
      echo "GenericBanditRunner,$K,$pow,$averages,$name,$out" >> $header
      ./$make_dir/efficient_multi_armed_bandits $header
      python3 plotting/plot_regret.py $out $plt_out
    done

}
for i in 1 2 3 4 5
do
  run_experiment $i & disown
done