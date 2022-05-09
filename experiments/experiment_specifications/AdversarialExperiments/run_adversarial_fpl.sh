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
#averages=100
averages=25
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

    out_tent=$tmp_dir/$name$1_tent.out
    plt_out_tent=$tmp_dir/$name$1_tent.png

    rm $header $out $plt_out $out_mod2 $plt_out_mod2 $out_stochastic $plt_out_stochastic $out_tent $plt_out_tent 2>/dev/null

    echo "runner,dataset,gap,k,rounds,averages,delta,output_path,optimal_probability,optimal_proportion" >>$header
    echo "fpl_adversarial,stochastically_constrained_adversarial,3.2,$1,$rounds,$averages,$delta,$out,0.8,0.3" >> $header
    echo "fpl_adversarial,mod2,3.2,$1,$rounds,$averages,$delta,$out_mod2,0.9,0.2" >> $header
    echo "fpl_adversarial,TentMapDataset,3.2,$1,$rounds,$averages,$delta,$out_stochastic,0.9,0.2" >> $header

    ./$make_dir/efficient_multi_armed_bandits $header
    python3 plotting/plot_compare.py $out $plt_ou
    python3 plotting/plot_compare.py $out_mod2 $plt_out_mod2
    python3 plotting/plot_compare.py $out_tent $plt_out_tent

}

#for k in 16 32 64 128
for k in 8 16 32 64 128; do 
    #for k in 16
    #for k in 1024 2048 4096 8192 16384
    run_experiment $k
done
zip $tmp_dir/$name.zip $tmp_dir/*.out
rm $tmp_dir/*header* 2>/dev/null
rm $tmp_dir/*.out* 2>/dev/null
