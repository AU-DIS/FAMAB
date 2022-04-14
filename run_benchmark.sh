#!/usr/bin/bash
rm *.csv
./cmake-build-heroicis/benchmark_bandits --benchmark_out=raw_out.csv --benchmark_out_format=csv
./process_benchmarks.sh raw_out.csv out.csv
echo "name,k,iterations,real_time,cpu_time,time_unit,bytes_per_second,items_per_second,label,error_occurred,error_message" >> sample.csv
echo "name,k,iterations,real_time,cpu_time,time_unit,bytes_per_second,items_per_second,label,error_occurred,error_message" >> update.csv
grep "sample" out.csv >> sample.csv
grep "update" out.csv >> update.csv
python3 plotting/benchmark.py sample.csv /mnt/ssd/bandits/sample.png
python3 plotting/benchmark.py update.csv /mnt/ssd/bandits/update.png