#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 8

int main(){

  //openmp usually takes the form of ...
  //#prama omp <construct> [<clause> [clause] ...
  //plugin to have console in atom platform io terminal

  //omp_set_num_threads(8);
  #pragma omp parallel
  {
    #pragma omp for
    for(int i = 0; i < NUM_THREADS; i++){
      printf("INSIDE OF LOOP, iteration %d\n", i);

    }

    printf("done now for thread: %i ", omp_get_thread_num());


  }



  return 0;
}
