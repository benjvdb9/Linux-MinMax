
#include <stdio.h> 
#include<stdlib.h>
#include<math.h>

  int size=0;
  int sizeArray;
   int j=0;
    int k=0;
    int n=6;
  int * getDigits(FILE *file){
  int buff[255] ; 
  int i=0;
 
   
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

            
             for(i=0;i<n;i++){
        for(j=0;j<sizeArray;j++){
            printf("%d ", *(intMatrix + i*sizeArray + j));
        }
            return intMatrix;
    
        }
        
        
        }

  }

    int main() 
    { 
    FILE  * file = fopen("le_fichier.txt", "r");

    int *intMatrix = getDigits(file);

    int i;
    for(i=0;i<n;i++){
        for(j=0;j<sizeArray;j++)
            printf("%d ", *(intMatrix + i*sizeArray + j));
        }
             printf(" \n");
   
  fclose(file);
  return 0; 
 
    }
