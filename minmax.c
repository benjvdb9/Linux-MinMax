#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *minmax(void *val);

int main()
{
	pthread_t tid, ti2;
	int message[5] = {3, 5, 9, 2};
	int message2[5] = {4, 1, 3, 99, 101};
	int iret, iret2;

	iret = pthread_create(&tid, NULL, minmax, (void*)message);
	iret2 = pthread_create(&ti2, NULL, minmax, (void*)message2);
	pthread_join(tid, NULL);

	return 0;
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

	int res[2];
	res[0] = min;
	res[1] = max;
	printf ("MIN: %d\n", res[0]);
	printf ("MAX: %d\n", res[1]);
}

