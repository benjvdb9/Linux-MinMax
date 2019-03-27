#include <stdlib.h> /* pour les constantes EXIT_SUCCESS ET EXIT_FAILURE */
#include <stdio.h> /* pour fprintf() */
#include <unistd.h> /* pour fork */
#include <sys/types.h> /* pour le type pid_t*/
#include <sys/errno.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>
#include "getDigits.h"

#define MSGSIZE 200



pid_t create_process();

clock_t start, end;

void *minmax(void *val);

void terminer(void)
{
  printf("j'ai terminer\n");
}



int main ()
{
  start = clock();

  int ip=0;
  int np=0;
  int jp=0;


	char buffer1[MSGSIZE];
	char buffer2[MSGSIZE];
	char inbuf[MSGSIZE];

	//char **pointer_out_pipe;
	int p[2] ; // the pipe
	pipe(p);
	int	*pipe_value; //	pipe data
	int op = 0;
	int nbytes;

  atexit(terminer);

	FILE  * file = fopen("data.txt", "r");


	struct MatrixLineCol filevalue;
	filevalue = getDigits(file);

	int sizeArray=filevalue.col;
	int lp= filevalue.line -1;
	int *intMatrix = filevalue.matrix;

	pid_t pid[lp];
	int codesortie[lp];


// loop to create process
	while(ip<=lp)
  {
    pid[ip] = create_process();
    if(pid[ip] ==0)
    {
				close(p[0]); //close in read
				struct data *t_pointer, thread_msg;
				thread_msg.size = sizeArray;
				thread_msg.numbers = intMatrix + (ip*sizeArray) - 1;
				t_pointer = &thread_msg;
				pipe_value = minmax(t_pointer);

				close(p[0]); //close in read
				sprintf(buffer1, "%d",pipe_value[0] );
				sprintf(buffer2, "%d",pipe_value[1] );
				write(p[1],buffer1 ,MSGSIZE);
				write(p[1],buffer2,MSGSIZE);
				printf("je suis le fils %d avec PID %d et de pipe_value: %d et %d\n "
				, (int) ip, (int) getpid(), pipe_value[0], pipe_value[1]);



      	_exit(0); // don't exec the function "atexit" for the child
        break;
      }
      else
      {
        ip++;

      }
    }

//loop to wait the end of différents process
		while(np<=lp){
			pid[np] = waitpid(pid[np], &codesortie[np], WUNTRACED );
			np++;
		}

//verification of the children answers
		while(jp<=lp){
			if (WIFEXITED(codesortie[jp])){
				printf("le fils %d s'est terminé normalement"
				"avec le code de sortie  %d\n" ,  pid[jp], WEXITSTATUS(codesortie[jp]));
			}

			jp++;
		}


  int out_pipe[2*lp+2];
  printf("je suis le père  avec PID %d\n" ,  (int) getpid());

	while((nbytes = read(p[0],inbuf,MSGSIZE ))!= 0)
	{
		close(p[1]);
		out_pipe[op]=atoi (inbuf);
		if (op > MSGSIZE){
			break;
		}else{
			op++;
		}
	}

	struct data *t_pointer, thread_msg;

	thread_msg.size = sizeof(out_pipe)/sizeof(out_pipe[0]);
  printf("la size est %d", thread_msg.size);
	thread_msg.numbers = out_pipe - 1;
	t_pointer = &thread_msg;

	minmax(t_pointer);

	end = clock();
	double cpu_time = ((double) (end - start) * 1000) / CLOCKS_PER_SEC;
	printf("\nTIME: %fms\n", cpu_time);
	copyMemUse();

	exit(0); //execution of  function "atexit" for the father

	return 0;
}

pid_t create_process()
{
  pid_t pid;
  do {
    pid = fork();

  } while ((pid == -1) && (errno ==EAGAIN));
  return pid;
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

static	int res[2];
	res[0] = min;
	res[1] = max;
	printf ("MIN: %d\n", res[0]);
	printf ("MAX: %d\n", res[1]);
	//_exit(0);
	return res;
}
