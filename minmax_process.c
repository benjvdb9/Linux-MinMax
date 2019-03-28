#include <stdlib.h> /* pour les constantes EXIT_SUCCESS ET EXIT_FAILURE */
#include <stdio.h> /* for fprintf() */
#include <unistd.h> /* for fork */
#include <sys/types.h> /* for the type pid_t*/
#include <sys/errno.h>
#include <sys/wait.h> /* for the  system wait*/
#include <string.h>
#include <time.h>
#include "getDigits.h"

#define MSGSIZE 200


/* declaration function*/
pid_t create_process();
void *minmax(void *val);
void endprocess();


/*management of the clock*/
clock_t start, end;


int main ()
{

  start = clock();

  int ip=0;
  int np=0;
  int jp=0;


	char buffer1[MSGSIZE];
	char buffer2[MSGSIZE];
	char inbuf[MSGSIZE];

	int p[2] ; // declaration of  pipe
	pipe(p);
	int	*pipe_value; //	pipe data
	int op = 0;
	int nbytes;

  //atexit(endprocess);

  /* open file*/
	FILE  * file = fopen("data.txt", "r");


	struct MatrixLineCol filevalue;
	filevalue = getDigits(file);

	int sizeArray=filevalue.col;
	int lp= filevalue.line -1;
	int *intMatrix = filevalue.matrix;

	pid_t pid[lp]; //create array to save differents pid
	int codesortie[lp];


// loop to create process
	while(ip<=lp)
  {
    pid[ip] = create_process();
    if(pid[ip] ==0)
    {
			/*manage the son*/
				struct data *t_pointer, thread_msg; // create struct data
				thread_msg.size = sizeArray;
				thread_msg.numbers = intMatrix + (ip*sizeArray) - 1;
				t_pointer = &thread_msg;
				pipe_value = minmax(t_pointer); //return min max to pipe_value

				close(p[0]); //close in read
				sprintf(buffer1, "%d",pipe_value[0] ); // put min in the buffer1
				sprintf(buffer2, "%d",pipe_value[1] ); // put min in the buffer2
				write(p[1],buffer1 ,MSGSIZE);// write buffer1 in the pipe
				write(p[1],buffer2,MSGSIZE); // write buffer2 in the
				// printf("je suis le fils %d avec PID %d et de pipe_value: %d et %d\n "
				// , (int) ip, (int) getpid(), pipe_value[0], pipe_value[1]);
      	_exit(0); // don't exec the function "atexit" for the son
        break; // stop the execution when it's a son
      }
      else
      {
        ip++;

      }
    }

//loop to wait the end of différents processes
		while(np<=lp){
			pid[np] = waitpid(pid[np], &codesortie[np], WUNTRACED );
			np++;
		}

//verification  children answers
		// while(jp<=lp){
		// 	if (WIFEXITED(codesortie[jp])){ //WIFEXITED(status) : returns true if the child terminated normally
		// 		printf("le fils %d s'est terminé normalement"
		// 		"avec le code de sortie  %d\n" ,  pid[jp], WEXITSTATUS(codesortie[jp])); /*WEXITSTATUS(status) : returns the exit status of the child.
    //     This macro should be employed only if WIFEXITED returned true.*/
		// 	}
    //
		// 	jp++;
		// }


  int out_pipe[2*lp+2]; // array to manage the out of the pipe
//  printf("je suis le père  avec PID %d\n" ,  (int) getpid());

//loop to read th pipe
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

  //treatement of the father
	struct data *t_pointer, thread_msg;
	thread_msg.size = sizeof(out_pipe)/sizeof(out_pipe[0]);
  //printf("la size est %d", thread_msg.size);
	thread_msg.numbers = out_pipe - 1;
	t_pointer = &thread_msg;
	pipe_value  = minmax(t_pointer); // execute minmax on values return by differents childen to the father
  printf(" le MIN est : %d", pipe_value[0]);
  printf(" le MAX est : %d", pipe_value[1]);


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
	 //printf("START\n");
	for (int i=1; i<=sizeVals; i++)
	{
		if(min > values[i]){
			min = values[i];
		}
		if(max < values[i]){
			max = values[i];
		}
		//printf("%d\n", values[i]);
	}

static	int res[2];
	res[0] = min;
	res[1] = max;
	//printf ("MIN: %d\n", res[0]);
	//printf ("MAX: %d\n", res[1]);
	//_exit(0);
	return res;
}

void  endprocess()
{
  printf("the father has finished his job, thanks!\n");

}
