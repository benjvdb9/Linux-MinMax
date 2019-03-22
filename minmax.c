#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include<math.h>

void *minmax(void *val);
void newthread(void *message);

int threads = 6;
int global_min;
int global_max;
pthread_mutex_t lock;

int size=0;
int sizeArray;
int i=0,j=0;
int k=0;
int n;

struct MatrixLigneCol
{
	int *matrix;
	int ligne, col;
};


struct MatrixLigneCol getDigits(FILE *file)
{
	int buff[255] ;
	int i=0;

	printf("choisez le nombre de processus ");
	scanf("%d",&n);

	if (file == NULL)
	{
		printf("Error! Could not open file\n");
		exit(-1);
	}else{
	while (fscanf(file, "%d", buff+i) != EOF){
		size++;
		i++;
	}
        sizeArray=size/n;
        int *intMatrix =(int *) malloc(n * sizeArray * sizeof(int));
        for(i=0;i<n;i++){
        	for(j=0;j<sizeArray;j++){
			*(intMatrix + i*sizeArray + j)=*(buff+k+j);
		}
		k=k+sizeArray;
	}

	struct MatrixLigneCol fileValueMa;
	fileValueMa.col=sizeArray;
	fileValueMa.ligne=n;
	fileValueMa.matrix=intMatrix;

	return fileValueMa;
	}}

int test()
{
	FILE  * file = fopen("le_fichier.txt", "r");


	struct MatrixLigneCol filevalue;
	filevalue = getDigits(file);

	int sizeArray=filevalue.col;
	int n= filevalue.ligne;
	int *intMatrix = filevalue.matrix;

	for(i=0;i<n;i++){
		for(j=0;j<sizeArray;j++){
			printf("%d ", *(intMatrix + i*sizeArray + j));
			printf("\n");
		}
	}

	printf("% d  %d ",n  ,sizeArray);
	fclose(file);
	return 0;
}

struct data
{
	int size;
	int *numbers;
};

int main()
{
	FILE  * file = fopen("le_fichier.txt", "r");


	struct MatrixLigneCol filevalue;
	filevalue = getDigits(file);

	int sizeArray=filevalue.col;
	int n= filevalue.ligne;
	int *intMatrix = filevalue.matrix;

	int message[5] = {3, 5, 9, 2};
	int message2[5] = {4, 1, 3, 99, 101};

	for(int i=0; i<n; i++){
		struct data *t_pointer, thread_msg;
		thread_msg.size = sizeArray;
		thread_msg.numbers = intMatrix + (i*sizeArray) - 1;
		t_pointer = &thread_msg;
		newthread(t_pointer);
	}
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
