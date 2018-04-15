#!/bin/bash
uptime

#sequential
#standard execution
for ((i=0; i<7; i+=1)); do ./main.out 12000 5 4000 10 4 20 -1 no < input_cos\(x\)-pow\(x\,3\)10-3.txt ; done

#less trees
for ((i=0; i<7; i+=1)); do ./main.out 3000 5 1000 10 4 20 -1 no < input_cos\(x\)-pow\(x\,3\)10-3.txt ; done

#more input points
for ((i=0; i<7; i+=1)); do ./main.out 12000 5 4000 10 4 20 -1 no < input_cos\(x\)-pow\(x\,3\)10-4.txt ; done

#fastflow
#standard execution
for((j=1; j<=16; j*=2)); do
	for ((i=0; i<7; i+=1)); do ./ff_main.out 12000 5 4000 10 4 20 -1 $j no < input_cos\(x\)-pow\(x\,3\)10-3.txt ; done done

#less trees
for((j=1; j<=16; j*=2)); do
	for ((i=0; i<7; i+=1)); do ./ff_main.out 3000 5 1000 10 4 20 -1 $j no < input_cos\(x\)-pow\(x\,3\)10-3.txt ; done done

#more input points
for((j=1; j<=16; j*=2)); do
	for ((i=0; i<5; i+=1)); do ./ff_main.out 12000 5 4000 10 4 20 -1 $j no < input_cos\(x\)-pow\(x\,3\)10-4.txt ; done done


#threads
#standard execution
for((j=1; j<=16; j*=2)); do
	for ((i=0; i<7; i+=1)); do ./thread_main.out 12000 5 4000 10 4 20 -1 $j no < input_cos\(x\)-pow\(x\,3\)10-3.txt ; done done

#less trees
for((j=1; j<=16; j*=2)); do
	for ((i=0; i<7; i+=1)); do ./thread_main.out 3000 5 1000 10 4 20 -1 $j no < input_cos\(x\)-pow\(x\,3\)10-3.txt ; done done

#more input points
for((j=1; j<=16; j*=2)); do
	for ((i=0; i<5; i+=1)); do ./thread_main.out 12000 5 4000 10 4 20 -1 $j no < input_cos\(x\)-pow\(x\,3\)10-4.txt ; done done
