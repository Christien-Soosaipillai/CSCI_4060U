#include <stdio.h>
#include <omp.h>
#define NUM_THREADS 4

int main(){

  int i;
  double result[NUM_THREADS];

  #pragma omp parallel for
  for(i = 0; i < NUM_THREADS; i++){
    int j = 5 + 2*(i+1);
    result[i] = 5*6*7 +j;
    printf("result for iteration %d is %f\n", i, result[i]);

  }

  return 0;
}

// int i;
// double result[NUM_THREADS];
// omp_set_num_threads(NUM_THREADS);
// int j = 5;
//
//
//   for(i = 0; i < NUM_THREADS; i++){
//     j += 2;
//     result[i] = 5*6*7 +j;
//     printf("result for iteration %d is %f\n", i, result[i]);
//   }
