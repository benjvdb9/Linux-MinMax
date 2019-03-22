#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *minmax(void *val);
void newthread(int message[]);

int threads = 6;
int global_min;
int global_max;
pthread_mutex_t lock;

int main()
{
	int message[5] = {3, 5, 9, 2};
	int message2[5] = {4, 1, 3, 99, 101};

	for(int i=0; i<threads; i++){
		newthread(message2);
	}
	return 0;
}

void newthread(int message[])
{
	void *status;
	pthread_t tid;
	int iret;

	pthread_mutex_init(&lock, NULL);
	iret = pthread_create(&tid, NULL, minmax, (void*)message);
	pthread_join(tid, &status);
}

void *minmax(void *val)
{
	int *values;
	values = (int *) val;
	int size = values[0];

	int min = values[1];
	int max = values[1];
	for (int i=1; i<=size; i++)
	{
		if(min > values[i]){
			min = values[i];
		}
		if(max < values[i]){
			max = values[i];
		}
	}

	pthread_mutex_lock(&lock);
	if(min > global_min){
		global_min = min;
	}
	if(max < global_max){
		global_max = max;
	}
	pthread_mutex_unlock(&lock);

	int res[2];
	res[0] = min;
	res[1] = max;
	printf ("MIN: %d\n", res[0]);
	printf ("MAX: %d\n", res[1]);
	
	pthread_exit((void*) res);
}
