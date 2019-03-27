#include <stdio.h>
#include <stdlib.h>




//generate randown values between 0 and 100
int main()
{
  int i=0;
  int max=0;
  int value=0;


  int number_to_guess;

while (max<=0){
  printf("\nEnter the max value , [0,max] : ");
  scanf("%i",&max);
  if ( max <0)
  {
    printf("\nEnter a positive value  please!");
  }
  // if (typeof (max)!= int){
  //   printf("\nEnter a integer value please!");
  // }
}

while (value <=0){
  printf("\n How many randowm values : ");
  scanf("%i",&value);
  if ( value <0)
  {
    printf("\nEnter a positive value!");
  }
}


  FILE*  file = fopen("data.txt", "w");
  while(i <= value-1)
  {
    if (i==0)
    {
          printf("\nthese values will be add in the file data.txt:");
    }
     number_to_guess = rand() % max + 1;

    fprintf(file,"%d\n", number_to_guess);
    printf("\n%d\n",number_to_guess);
    i++;
  }

 printf("\n Super , values havent been written on the file data.txt \n");
 fclose(file);

return 0;
}
