#include <stdio.h>
#include <omp.h>
#define NUM_THREADS 5

int main(){

  int i;

  double result[NUM_THREADS];

  #pragma omp parallel if (NUM_THREADS > 4)
  {
    #pragma omp parallel for
    for(i = 0; i < NUM_THREADS; i++){
      result[i] = 6 * 6 * 6 + i;
      printf(" result for iteration %d is %f \n", i, result[i]);
    }
  }



  return 0;
}
