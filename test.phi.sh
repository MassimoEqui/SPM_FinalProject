#!/bin/bash
uptime

#sequntial
for ((i=0; i<7; i+=1)); do ./main.out 2400 5 800 10 20 -1 no < input_cos\(x\)-pow\(x\,3\)10-3.txt ; done

#fastflow
for ((i=0; i<7; i+=1)); do ./ff_main.out 2400 5 800 10 20 -1 1 no < input_cos\(x\)-pow\(x\,3\)10-3.txt ; done

for((j=2; j<=9; j+=1)); do
	for ((i=0; i<7; i+=1)); do ./ff_main.out 2400 5 800 10 20 -1 $j no < input_cos\(x\)-pow\(x\,3\)10-3.txt ; done done

for((j=10; j<=80; j+=10)); do
	for ((i=0; i<7; i+=1)); do ./ff_main.out 2400 5 800 10 20 -1 $j no < input_cos\(x\)-pow\(x\,3\)10-3.txt ; done done

#threads
for ((i=0; i<7; i+=1)); do ./thread_main.out 2400 5 800 10 20 -1 1 no < input_cos\(x\)-pow\(x\,3\)10-3.txt ; done

for((j=2; j<=9; j+=1)); do
	for ((i=0; i<7; i+=1)); do ./thread_main.out 2400 5 800 10 20 -1 $j no < input_cos\(x\)-pow\(x\,3\)10-3.txt ; done done

for((j=10; j<=80; j+=10)); do
	for ((i=0; i<7; i+=1)); do ./thread_main.out 2400 5 800 10 20 -1 $j no < input_cos\(x\)-pow\(x\,3\)10-3.txt ; done done
