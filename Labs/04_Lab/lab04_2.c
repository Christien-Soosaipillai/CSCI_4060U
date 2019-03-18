#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <omp.h>
#include <math.h>

#define N 10
#define NUM_THREADS 10

int sequence[N];

/*
HERE IS THE OUTPUT AND TIME SAMPLES
iteration 0 : 0
iteration 1 : 1
iteration 2 : 1
iteration 3 : 2
iteration 4 : 3
iteration 5 : 5
iteration 6 : 8
iteration 7 : 13
iteration 8 : 21
iteration 9 : 34

real	0m0.002s
user	0m0.002s
sys	0m0.000s

real	0m0.002s
user	0m0.000s
sys	0m0.002s

real	0m0.005s
user	0m0.005s
sys	0m0.002s


*/


int main(){

  int n1, n2, nextTerm, ittr = 0;

  omp_set_num_threads(NUM_THREADS);
  #pragma omp parallel for shared(n1, n2, nextTerm)
    for(int i = 0; i <= N; i++){
      
      #pragma omp task
        if(i == 0){
          n1 = 0;
          sequence[ittr] = i;
          ittr++;
          //printf("iteration %i : %i\n", i, i);
        }else if(i == 1){
          n2 = 1;
          //printf("iteration %i : %i\n", i, i);
          sequence[ittr] = i;
          ittr++;

        }else{
          nextTerm = n1 + n2;
          n1 = n2;
          n2 = nextTerm;
          //printf("iteration %i: %i\n", i, nextTerm);
          sequence[ittr] = nextTerm;
          ittr++;
        }
  }

  /*
   This is just to read them in order
   but I couldnt figure out how to read
   them in order in the parallel clause
   */
  for(int i = 0; i < N; i++ ){
    printf("iteration %i : %i\n", i, sequence[i]);

  }

  return 0;
}
