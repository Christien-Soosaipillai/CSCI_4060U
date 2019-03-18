#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <omp.h>
#include <math.h>

#define N 10
#define NUM_THREADS 10


int main(){

  int n1, n2, nextTerm = 0;


  for(int i = 0; i <= N; i++){
    if(i == 0){
      n1 = 0;
      printf("iteration %i : %i\n", i, i);
    }else if(i == 1){
      n2 = 1;
      printf("iteration %i : %i\n", i, i);


    }else{
      nextTerm = n1 + n2;
      n1 = n2;
      n2 = nextTerm;
      printf("iteration %i: %i\n", i, nextTerm);

    }
  }





  return 0;
}
