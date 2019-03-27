Min-Max
======

A function written in C for Linux designed to read a file containing a set of numbers and find the greatest and smallest number.
The function spilts up all the numbers after reading them and sends them to a configureable number of processes/threads and finds the local min&max for each segment before finally giving the global Min and Max as output.

There are two codes, one written with a process approach and the other with the thread approach, and both of them allow us to measure execution time and memory usage for comparison's sake.

##Usage

Process: gcc (-o name) minmax\_process.c
Thread:  gcc -pthread (-o name) minmax\_thread.c

However you can simply use ./compile.sh to compile both at once. Memory usage will be written in Thread\_Stats.txt after successfully executing the code. You can use add\_data.out to generate a data file of a configureable amount of values for testing use.
