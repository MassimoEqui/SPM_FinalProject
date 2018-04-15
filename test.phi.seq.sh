#!/bin/bash
uptime

#sequential
#standard execution
for ((i=0; i<7; i+=1)); do ./main.out 2400 5 800 10 20 -1 no < input_cos\(x\)-pow\(x\,3\)10-3.txt ; done

#less trees
for ((i=0; i<7; i+=1)); do ./main.out 1200 5 400 10 20 -1 no < input_cos\(x\)-pow\(x\,3\)10-3.txt ; done

#more input points
for ((i=0; i<5; i+=1)); do ./main.out 2400 5 800 10 20 -1 no < input_cos\(x\)-pow\(x\,3\)10-4.txt ; done
