#!/usr/bin/bash

# Clean up csv files
rm *.csv
rm /mnt/ssd/bandits/*.csv
# Run benchmarks and process them
./cmake-build-heroicis/benchmark_bandits --benchmark_out=raw_out.csv --benchmark_out_format=csv
./process_benchmarks.sh raw_out.csv out.csv
# Prepare output file swith headers
echo "name,k,iterations,real_time,cpu_time,time_unit,bytes_per_second,items_per_second,label,error_occurred,error_message" >> header

# Filter basic algorithms
rm /mnt/ssd/bandits/*.csv

#./filter_basic_benchmarks.sh

cat header sample_out.csv >> /mnt/ssd/bandits/sample.csv
cat header update_out.csv >> /mnt/ssd/bandits/update.csv
cat header combined.csv >> /mnt/ssd/bandits/combined.csv

#python3 plotting/benchmark.py /mnt/ssd/bandits/sample.csv /mnt/ssd/bandits/sample.png
#python3 plotting/benchmark.py /mnt/ssd/bandits/update.csv /mnt/ssd/bandits/update.png
#python3 plotting/benchmark.py /mnt/ssd/bandits/combined.csv /mnt/ssd/bandits/combined.png

#./filter_fpl_benchmarks.sh /tmp /mnt/ssd/bandits