#!/bin/bash
uptime

for ((i=0; i<12; i+=1)); do ./main.out 12000 5 4000 10 20 -1 no < input_cos\(x\)-pow\(x\,3\)10-3.txt ; done

for ((i=0; i<12; i+=1)); do ./parallel_main.out 12000 5 4000 10 20 -1 1 no < input_cos\(x\)-pow\(x\,3\)10-3.txt ; done

for((j=2; j<=16; j+=2)); do
	for ((i=0; i<12; i+=1)); do ./parallel_main.out 12000 5 4000 10 20 -1 $j no < input_cos\(x\)-pow\(x\,3\)10-3.txt ; done done
