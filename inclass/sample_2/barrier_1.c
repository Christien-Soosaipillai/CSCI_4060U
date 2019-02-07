#include <stdio.h>
#ifdef _OPENMP
  #include <omp.h>
#else
  #define omp_get_num_threads() 1
  #define omp_get_thread_num() 0
#endif

#define NUM_THREADS 16

int calc1(int threadID);
int calc2(int i, int [] a);

int A[NUM_THREADS];
int iterator = 0;

int main(){
  #ifdef _OPENMP
    omp_set_num_threads(NUM_THREADS);
  #endif
  #pragma omp parallel
  {
    int thread_id;
    thread_id = omp_get_thread_num();
    // //if(thread_id = threads 0 - 7)
    // //the bigger the data the higher the
    // //higher the chance of the program finishing
    // // the higher level ID's tha the lower ones
    // if(thread_id < omp_get_thread_num()/2){
    //   for(int i = 0; i < 1000000; i++ ){
    //
    //   }
    // }

    //Call calc 1(thread ID) and store result in array A[thread_ID]
    calc1(threadID);
    #pragma omp barrier
    //Call calc 2(thread ID, A) and store result in array b[thread_ID]
    calc2(thread_id, );

  }
}

int calc1(int threadID){
  iterator+=1;
  A[iterator] = threadID;

}


int calc2(int i, int a[]){



}
