#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>
#include <math.h>
#include "getDigits.h"

void *minmax(void *val);
void newthread(void *message);

//Global variables for thread communication
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

	//Extracting numbers from file into matrix struct
	struct MatrixLineCol filevalue;
	filevalue = getDigits(file);

	int sizeArray=filevalue.col;
	int n= filevalue.line;
	int *intMatrix = filevalue.matrix;

	global_min = intMatrix[0];
	global_max = intMatrix[0];

	//one newthread per line in matrix
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
	
	//time and memory stats
	end = clock();
	cpu_time = ((double) (end - start) * 1000) / CLOCKS_PER_SEC;
	printf("\nTIME: %fms\n", cpu_time);
	copyMemUse();
	fclose(file);
	free(intMatrix);
	return 0;
}

//creates thread running minmax(mes) with mes ~ (struct data *)
void newthread(void *message)
{
	void *status;
	pthread_t tid;
	int iret;

	iret = pthread_create(&tid, NULL, minmax, message);
}


void *minmax(void *val)
{
	//Extracting size and array from data struct pointer
	int *values;
	struct data *structvalues;
	structvalues = (struct data *) val;
	int sizeVals = structvalues->size;
	values =  structvalues->numbers;

	//comparing values for local min/max
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

	//Modify global min/max if needed
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
}
