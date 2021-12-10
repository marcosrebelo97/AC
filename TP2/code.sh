#!/bin/bash

>Questao2/questao02.csv

for((i=1; i<=30; i+=1)); do
    echo $i
    export OMP_NUM_THREADS=$i
    gcc -Wall -O0 amdahl.c -fopenmp -o amdahl
    mkdir -p Questao2
    ./amdahl $i  >> Questao2/questao02.csv
done



 
