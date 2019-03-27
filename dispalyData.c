  #include <stdio.h>
  #include<stdlib.h>
  #include<math.h>
  #include "getDigits.h"

   int main()
    {
        FILE  * file = fopen("data.txt", "r");
        int i,j;
        struct MatrixLineCol filevalue;
        filevalue = getDigits(file);

        int sizeArray=filevalue.col;
        int n= filevalue.ligne;
        int *intMatrix = filevalue.matrix;

        for(i=0;i<n;i++){
          for(j=0;j<sizeArray;j++)
              printf("%d ", *(intMatrix + i*sizeArray + j));
           printf("\n");
        }

        printf("% d  %d ",n  ,sizeArray);
        fclose(file);
        return 0;
    }
