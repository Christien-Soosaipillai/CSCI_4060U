#include <stdio.h>
#include <omp.h>
#define NUM_THREADS 3

int main(){

  int i, j, k;

  double result[NUM_THREADS][NUM_THREADS][NUM_THREADS];

  omp_set_num_threads(NUM_THREADS);

  #pragma omp for collapse(2) private(i,j,k)
  for(i = 0; i < NUM_THREADS; i++){

    for(j = 0; j < NUM_THREADS; j++){

      for( k = 0; k < NUM_THREADS; k++){
      result[i][j][k] = i * j * k;
      printf("Index[%d,%d,%d] = %f \n", i, j, k, result[i][j][k]);
      }
    }
  }
  return 0;
}
