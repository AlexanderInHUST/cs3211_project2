#!/bin/bash

for ((i = 1; i <= 4; i++)) do
    for ((j = 1; j <= 100000; j++)) do
        qsub par_$iX$i_$j.pbs
        qsub par_$iX$i_$j.pbs
    done
done