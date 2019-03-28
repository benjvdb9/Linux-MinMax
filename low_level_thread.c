#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>
#include <sched.h>
#include <signal.h>
#include <sys/wait.h>
#include "getDigits.h"

#define STACK 1024*64

int minmax(void *val);
void newthread(void *message);

int global_min;
int global_max;
int threads_completed = 0;
pthread_mutex_t lock;

int main()
{
	clock_t start, end;
	double cpu_time;
	start = clock();
	FILE  * file = fopen("data.txt", "r");

        
	struct MatrixLineCol filevalue;
	filevalue = getDigits(file);

	int sizeArray=filevalue.col;
	int n= filevalue.line;
	int *intMatrix = filevalue.matrix;

	global_min = intMatrix[0];
	global_max = intMatrix[0];

	pthread_mutex_init(&lock, NULL);
	for(int i=0; i<n; i++){
		struct data *t_pointer, thread_msg;
		thread_msg.size = sizeArray;
		thread_msg.numbers = intMatrix + (i*sizeArray) - 1;
		t_pointer = &thread_msg;
		newthread(t_pointer);
	}

	while(threads_completed < n);
	printf("GLOBAL MIN: %d\n", global_min);
	printf("GLOBAL MAX: %d\n", global_max);
	
	end = clock();
	cpu_time = ((double) (end - start) * 1000) / CLOCKS_PER_SEC;
	printf("\nTIME: %fms\n", cpu_time);
	copyMemUse();
	return 0;
}

void newthread(void *message)
{
	void *stack;
	pid_t pid;

	stack = malloc(STACK);
	if (stack == 0) {
		perror("could not allocate stack");
		exit(1);
	}

	pid = clone(&minmax, (char*) stack + STACK, SIGCHLD | CLONE_VM,
			message);

	if (pid == -1) {
		perror("clone");
		exit(2);
	}
}

int minmax(void *val)
{
	int *values;
	struct data *structvalues;
	structvalues = (struct data *) val;
	int sizeVals = structvalues->size;
	values =  structvalues->numbers;

	int min = values[1];
	int max = values[1];
	for (int i=1; i<=sizeVals; i++)
	{
		if(min > values[i]){
			min = values[i];
		}
		if(max < values[i]){
			max = values[i];
		}
	}

	pthread_mutex_lock(&lock);
	if(min < global_min){
		global_min = min;
	}
	if(max > global_max){
		global_max = max;
	}
	threads_completed++;
	pthread_mutex_unlock(&lock);

	//printf ("MIN: %d\n", min);
	//printf ("MAX: %d\n", max);
	return 0;
}
