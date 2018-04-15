#!/bin/bash
uptime

#sequential
for ((i=0; i<7; i+=1)); do ./main.out 12000 5 4000 10 4 20 -1 no < input_cos\(x\)-pow\(x\,3\)10-3.txt ; done

#fastflow
#for ((i=0; i<7; i+=1)); do ./ff_main.out 12000 5 4000 10 4 20 -1 1 no < input_cos\(x\)-pow\(x\,3\)10-3.txt ; done

for((j=1; j<=16; j*=2)); do
	for ((i=0; i<7; i+=1)); do ./ff_main.out 12000 5 4000 10 4 20 -1 $j no < input_cos\(x\)-pow\(x\,3\)10-3.txt ; done done

for((j=1; j<=16; j*=2)); do
	for ((i=0; i<7; i+=1)); do ./ff_main.out 3000 5 1000 10 4 20 -1 $j no < input_cos\(x\)-pow\(x\,3\)10-3.txt ; done done

for((j=1; j<=16; j*=2)); do
	for ((i=0; i<5; i+=1)); do ./ff_main.out 12000 5 4000 10 4 20 -1 $j no < input_cos\(x\)-pow\(x\,3\)10-4.txt ; done done


#threads
#for ((i=0; i<7; i+=1)); do ./thread_main.out 12000 5 4000 10 4 20 -1 1 no < input_cos\(x\)-pow\(x\,3\)10-3.txt ; done

for((j=1; j<=16; j*=2)); do
	for ((i=0; i<7; i+=1)); do ./thread_main.out 12000 5 4000 10 4 20 -1 $j no < input_cos\(x\)-pow\(x\,3\)10-3.txt ; done done

for((j=1; j<=16; j*=2)); do
	for ((i=0; i<7; i+=1)); do ./thread_main.out 3000 5 1000 10 4 20 -1 $j no < input_cos\(x\)-pow\(x\,3\)10-3.txt ; done done

for((j=1; j<=16; j*=2)); do
	for ((i=0; i<5; i+=1)); do ./thread_main.out 12000 5 4000 10 4 20 -1 $j no < input_cos\(x\)-pow\(x\,3\)10-4.txt ; done done
