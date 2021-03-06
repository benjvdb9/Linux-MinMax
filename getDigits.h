#ifndef FILE_TEST_H
#define FILE_TEST_H

  #include <stdio.h>
  #include<stdlib.h>
  #include<math.h>
  #include <ctype.h>

//Define the MatrixLineColumn   structure 
    struct MatrixLineCol
    {
        int *matrix;
        int line, col;
    };

// Define the data structure  
    struct data
    {
        int size;
        int *numbers;
    };   

// Get the digits from  the file and put them in a matrix 
    struct MatrixLineCol getDigits(FILE *file){
        int buff[10000] ;
        int size=0;
        int sizeArray;
        int i=0,j=0;
        int k=0;
        int n;

        // check  if there is a file 
        if (file == NULL)
        {
            printf("Error! Could not open file\n");
            exit(-1);
        }else{
            /* Read  every digit from  the file  and put them  in the buffer 
            and calculate the number of digits in the file  */
            while (fscanf(file, "%d", buff+i) != EOF){
                size++;
                i++;
            }
            /* check if the number of thread/process chose by the user 
            is less than the number of digits in the file */
            do{
              
                printf("choose the number of processes or threads :");
                scanf("%d",&n);
                //check if input is not a number
                if (!isdigit(n)){
                    printf("Entered input is not a number\n");
                }
    
                if(n>size)
                     printf("The number of the  processes or threads must be less than number of digits in the file ");
            }while(n>size);
            

            sizeArray=size/n;
            //create a matrix 
            int *intMatrix =(int *) malloc(n * sizeArray * sizeof(int));

            //fill the matrix
            for(i=0;i<n;i++){
                for(j=0;j<sizeArray;j++){
                    *(intMatrix + i*sizeArray + j)=*(buff+k+j);
                    }
                    k=k+sizeArray;
            }
            
            struct MatrixLineCol fileValueMa;
            fileValueMa.col=sizeArray;
            fileValueMa.line=n;
            fileValueMa.matrix=intMatrix;

            return fileValueMa;
        }

    }

    //Copies the content of /proc/self/status contaning
    //all the Memory usage stats to a file
    void copyMemUse()
    {
        char ch;
        FILE *source, *target;

        source = fopen("/proc/self/status", "r");

        if (source == NULL)
        {
            exit(EXIT_FAILURE);
        }

        target = fopen("Thread_Stats.txt", "w");

        while((ch = fgetc(source)) != EOF)
            fputc(ch, target);

        printf("See Thread_Stats.txt for Memory Usage.\n");
        fclose(source);
        fclose(target);
    }

#endif /* FILE_TEST_H */
