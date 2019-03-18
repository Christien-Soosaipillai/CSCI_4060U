#include <stdio.h>
#include <omp.h>
#define NUM_THREADS 4

int main(){

  int i = 0;

  double result[NUM_THREADS];
  double result2[NUM_THREADS];

  #pragma omp parallel
  {
    #pragma omp for 
    for(i = 0; i < NUM_THREADS; i++){
      printf("start of loop 1, iteration %d\n", i);
      result[i] = 6 * 6 * 6 + i;
      printf("LOOP 1: result for iteration %d is %f \n", i, result[i]);

    }

    //If no wait not included then their is an implicit barrier that exists.
    //If included second loop wont wait for all threads of the first loop to
    //complete running


    // #pragma omp for
    // for(i = 0; i < NUM_THREADS; i++){
    //   printf("start of loop 2, iteration %d\n", i);
    //   int j= 5 + 2 *(1+1);
    //   result2[i] = 6 * 6 * 6 + j;
    //   printf("LOOP 2: result for itteration %d is %f \n", i, result2[i]);
    // }

  }

  // for(i = 0; i < NUM_THREADS; i++){
  //   printf("start of loop 1, iteration %d\n", i);
  //   result[i] = 6 * 6 * 6 + i;
  //   printf("LOOP 1: result for iteration %d is %f \n", i, result[i]);
  //
  // }


  return 0;
}
