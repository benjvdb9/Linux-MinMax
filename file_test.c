
#include <stdio.h> 
#include<stdlib.h>
  
int main() 
{ 
  FILE *fp = fopen("le_fichier.txt", "r"); 
  int ch = getc(fp); 
  int size=0,i=0;
  int *buf=NULL;
  while (ch != EOF)  
  { 
    /* display contents of file on screen */ 
    putchar(ch);  
     if (isdigit(ch))
            size++;
    ch = getc(fp); 
  } 
  printf("size %d",size);

   buf = malloc(size*sizeof(int));
    fseek( fp, 0, SEEK_SET );
     while (fscanf(fp, "%d", buf+i) != EOF) {
            ++i;
            printf("rr");
        }
        
    for (i = 0; i < size; i++)
    {
        printf("Number is: %d\n\n", *(buf+i));
    }

  return 0; 
} 
