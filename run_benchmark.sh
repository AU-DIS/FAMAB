#!/usr/bin/bash
rm *.csv
./cmake-build-release-odin/benchmark_bandits --benchmark_out=out.csv --benchmark_out_format=csv
