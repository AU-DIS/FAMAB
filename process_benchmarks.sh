#!/bin/bash

sed 's/exp3/Exp3/g' $1 |
    sed 's/name,/name,k,/g' |
    sed 's/"//g' |
    sed 's/benchmark_//g' |
    sed 's/\/threads:15//g' |
    sed 's/\/threads:5//g' |
    sed 's/\/threads:1//g' |
    sed 's/\/1/,1/g' |
    sed 's/_sample/ (sample)/g' |
    sed 's/_update/ (update)/g' |
    sed 's/qbl/QBL/g' |
    sed 's/fpl/FPL/g' |
    sed 's/tsallis/Tsallis/g' |
    sed 's/_optimized/ (optimized)/g' |
    sed 's/_rv/ (RV)/g' |
    sed 's/_iw/ (IW)/g' |
    sed 's/_heap/ heap/g' >> $2


