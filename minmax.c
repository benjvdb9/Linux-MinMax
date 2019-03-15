#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int res[2];
int size = 2;
void *minmax(void *val);

int main()
{
	pthread_t tid, ti2;
	int message[3] = {5, 9, 99};
	int message2[4] = {5, 9, 99, 101};
	int iret, iret2;

	iret = pthread_create(&tid, NULL, minmax, (void*)message);
	iret2 = pthread_create(&ti2, NULL, minmax, (void*)message2);
	pthread_join(tid, NULL);

	printf ("Thread 1 finished: %d\n", res[0]);
	printf ("Thread 2 finished: %d\n", res[1]);
	return 0;
}

void *minmax(void *val)
{
	int *values;
	values = (int *) val;
	int size = sizeof(values)/sizeof(int);

	int min = values[0];
	int max = values[0];
	for (int i=0; i<size; i++)
	{
		if(min > values[i]){
			min = values[i];
		}
		if(max < values[i]){
			max = values[i];
		}
		printf("%d\n", i);
	}

	res[0] = min;
	res[1] = max;
}

