  #include <stdio.h> 
  #include<stdlib.h>
  #include<math.h>
  #include "get_digits.h"

int main() 
    { 
        int i,j;
        FILE  * file = fopen("le_fichier.txt", "r");

        struct MatrixLineColumn filevalue;
        filevalue = getDigits(file);

        int sizeArray=filevalue.col;
        int n= filevalue.line;
        int *intMatrix = filevalue.matrix;
        
        for(i=0;i<n;i++){
          for(j=0;j<sizeArray;j++)
              printf("%d ", *(intMatrix + i*sizeArray + j));
           printf("\n");
        }

        printf("% d  %d ",n  ,sizeArray);
        fclose(file);
        return 0; 
        system("pause");
   
}