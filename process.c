#include <stdlib.h> /* pour les constantes EXIT_SUCCESS ET EXIT_FAILURE */
#include <stdio.h> /* pour fprintf() */
#include <unistd.h> /* pour fork */
#include <sys/types.h> /* pour le type pid_t*/
#include <sys/errno.h>
#include "file_test.h"

int message[] = {3, 5, 9, 2};
int res[2];



pid_t create_process()
{
  pid_t pid;
  do {
    pid = fork();

  } while ((pid == -1) && (errno ==EAGAIN));
  return pid;
}


int* minmax(void *val)
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

	res[0] = min;
	res[1] = max;
  return res;
}





int main ()
{


FILE  * file = fopen("le_fichier.txt", "r");


  int i=1;
  pid_t pid[4];




  while(i<4)
  {
    pid[i] = create_process();
    if ( pid[i] == 0) {

      break;
    }else if(pid[i] != 0) {
      i++;
    }
    printf("%d.\n", pid[i] );
  }



  return 0;
}
