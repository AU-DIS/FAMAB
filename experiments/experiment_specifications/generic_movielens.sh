alias python3="/home/tversted/miniconda3/bin/python"
#alias python3="/opt/homebrew/bin/python3"

tmp_dir=/home/tversted/tmp

run_experiment() {
    n=10
    m=$1
    averages=40
    for ((j=1, pow=n; j<m; j++)); do ((pow *= n)); done


    header=$tmp_dir/header_movielens$1
    out=$tmp_dir/movielens$1.out
    plt_out=$tmp_dir/movielens$1.png
    rm $header $out $plt_out 2> /dev/null

    echo "runner,rounds,averages,dataset,output_path" >> $header
    echo "GenericBanditRunner,$pow,$averages,movielens,$out" >> $header
    ./cmake-build-release-odin/efficient_multi_armed_bandits $header
    python3 plotting/plot_regret.py $out $plt_out

}

for i in 1 2 3 4
do
  run_experiment $i & disown
done