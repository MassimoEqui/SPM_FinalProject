#!/bin/bash
uptime

#sequential
#standard execution
for ((i=0; i<7; i+=1)); do ./main.out 12000 5 4000 10 4 20 -1 no < input_cos\(x\)-pow\(x\,3\)10-3.txt ; done

#less trees
for ((i=0; i<7; i+=1)); do ./main.out 3000 5 1000 10 4 20 -1 no < input_cos\(x\)-pow\(x\,3\)10-3.txt ; done

#more input points
for ((i=0; i<7; i+=1)); do ./main.out 12000 5 4000 10 4 20 -1 no < input_cos\(x\)-pow\(x\,3\)10-4.txt ; done
