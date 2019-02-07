#include <stdio.h>
#include <omp.h>

void output(int ID);

int main(){

  //openmp usually takes the form of ...
  //#prama omp <construct> [<clause> [clause] ...
  //plugin to have console in atom platform io terminal

  omp_set_num_threads(8);
  #pragma omp parallel
  {

    int threadID = omp_get_thread_num();
    output(threadID);

  }

  printf("Program done\n");


  return 0;
}

void output(int ID){
    printf("hello (thread %d)\n", ID);
    printf("world (thread %d)\n", ID);

  }
