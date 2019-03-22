  #include <stdio.h> 
  #include<stdlib.h>
  #include<math.h>

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
    
    
    struct MatrixLigneCol getDigits(FILE *file){
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
        }

    }

    int main() 
    { 
        FILE  * file = fopen("le_fichier.txt", "r");

        
     

        struct MatrixLigneCol filevalue;
        filevalue = getDigits(file);

        int sizeArray=filevalue.col;
        int n= filevalue.ligne;
        int *intMatrix = filevalue.matrix;
        
     // int i;
        for(i=0;i<n;i++){
          for(j=0;j<sizeArray;j++)
              printf("%d ", *(intMatrix + i*sizeArray + j));
           printf("\n");
        }

        printf("% d  %d ",n  ,sizeArray);
        fclose(file);
        return 0; 
   
      }
