#ifndef FILE_TEST_H
#define FILE_TEST_H

  #include <stdio.h>
  #include<stdlib.h>
  #include<math.h>

//create MatrixLineColumn type 
    struct MatrixLineCol
    {
        int *matrix;
        int line, col;
    };

// create data type
    struct data
    {
        int size;
        int *numbers;
    };   

// Get digits from file and put them in a matrix 
    struct MatrixLineCol getDigits(FILE *file){
        int buff[255] ;
        int size=0;
        int sizeArray;
        int i=0,j=0;
        int k=0;
        int n;

        printf("choose the number of processes or threads : ");
        scanf("%d",&n);

        // test if there is a file 
        if (file == NULL)
        {
            printf("Error! Could not open file\n");
            exit(-1);
        }else{
            //read  evry digit from file  and put it in the buff
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
