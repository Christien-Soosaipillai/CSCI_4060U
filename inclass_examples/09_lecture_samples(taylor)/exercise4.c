#include <stdio.h>
#include <omp.h>
#define NUM_THREADS 8

int main(){

  int i;
  int j = 5;

  double result[NUM_THREADS];

  #pragma omp parallel for ordered
  for(i = 0 ; i < NUM_THREADS; i++){

    #pragma omp ordered
    j += 2;
    result[i] = 6 * 6 * 6 + j;
    #pragma omp ordered
    printf("result for iteration %d is %f \n", i, result[i]);
  }




  return 0;
}
