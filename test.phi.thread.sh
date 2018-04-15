#!/bin/bash
uptime

#threads
#standard execution
for((j=1; j<=128; j*=2)); do
	for ((i=0; i<7; i+=1)); do ./thread_main.out 2400 5 800 10 4 20 -1 $j no < input_cos\(x\)-pow\(x\,3\)10-3.txt ; done done

#less trees
for((j=1; j<=128; j*=2)); do
	for ((i=0; i<7; i+=1)); do ./thread_main.out 1200 5 400 10 4 20 -1 $j no < input_cos\(x\)-pow\(x\,3\)10-3.txt ; done done

#more input points
for((j=1; j<=128; j*=2)); do
	for ((i=0; i<5; i+=1)); do ./thread_main.out 2400 5 800 10 4 20 -1 $j no < input_cos\(x\)-pow\(x\,3\)10-4.txt ; done done
