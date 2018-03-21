#!/bin/bash
uptime

for ((i=0; i<12; i+=1)); do ./main_mic.out 2400 5 800 10 20 -1 no < input_cos\(x\)-pow\(x\,3\)10-3.txt ; done

for ((i=0; i<12; i+=1)); do ./parallel_main_mic.out 2400 5 800 10 20 -1 1 no < input_cos\(x\)-pow\(x\,3\)10-3.txt ; done

for((j=10; j<=120; j+=10)); do
	for ((i=0; i<12; i+=1)); do ./parallel_main_mic.out 2400 5 800 10 20 -1 $j no < input_cos\(x\)-pow\(x\,3\)10-3.txt ; done done
