#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>
#include<math.h>

void *minmax(void *val);
void newthread(void *message);

int global_min;
int global_max;
int threads_completed = 0;
pthread_mutex_t lock;

int size=0;
int sizeArray;
int i=0,j=0;
int k=0;
int n;

int main()
{
	clock_t start, end;
	double cpu_time;
	start = clock();
	FILE  * file = fopen("le_fichier.txt", "r");

        
	struct MatrixLigneCol filevalue;
	filevalue = getDigits(file);

	int sizeArray=filevalue.col;
	int n= filevalue.ligne;
	int *intMatrix = filevalue.matrix;

	global_min = intMatrix[0];
	global_max = intMatrix[0];

	for(int i=0; i<n; i++){
		struct data *t_pointer, thread_msg;
		thread_msg.size = sizeArray;
		thread_msg.numbers = intMatrix + (i*sizeArray) - 1;
		t_pointer = &thread_msg;
		newthread(t_pointer);
	}

	while(threads_completed < n);
	printf("GLOBAL MAX: %d\n", global_max);
	printf("GLOBAL MIN: %d\n", global_min);
	
	end = clock();
	cpu_time = ((double) (end - start) * 1000) / CLOCKS_PER_SEC;
	printf("\nTIME: %fms\n", cpu_time);
	copyMemUse();
	return 0;
}

void newthread(void *message)
{
	void *status;
	pthread_t tid;
	int iret;

	pthread_mutex_init(&lock, NULL);
	iret = pthread_create(&tid, NULL, minmax, message);
	pthread_join(tid, &status);
}

void *minmax(void *val)
{
	int *values;
	struct data *structvalues;
	structvalues = (struct data *) val;
	int sizeVals = structvalues->size;
	values =  structvalues->numbers;

	int min = values[1];
	int max = values[1];
	printf("START\n");
	for (int i=1; i<=sizeVals; i++)
	{
		if(min > values[i]){
			min = values[i];
		}
		if(max < values[i]){
			max = values[i];
		}
		printf("%d\n", values[i]);
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

	int res[2];
	res[0] = min;
	res[1] = max;
	printf ("MIN: %d\n", res[0]);
	printf ("MAX: %d\n", res[1]);

	pthread_exit((void*) res);
}
