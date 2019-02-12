#include <stdio.h>
#ifdef _OPENMP
  #include <omp.h>
#else
  #define omp_get_num_threads() 1
  #define omp_get_thread_num() 0
#endif

#define NUM_THREADS 16

/////////////////////////////////////////////////////

/* PURPOSE OF PROGRAM
an example of parallelization using a barrier
*/

/////////////////////////////////////////////////////

int main() {
  #ifdef _OPENMP
    omp_set_num_threads(NUM_THREADS);
  #endif
  #pragma omp parallel
  {
    int thread_id;
    thread_id = omp_get_thread_num();
    if (thread_id < omp_get_num_threads()/2) {
      for (int i=0; i< 10000000; i++) {

      }
    }
    printf("thread_id (before barrier) = %d\n", thread_id);
    #pragma omp barrier
    //the barrier causes all threads to wait until other
    //threads have caught up before proceedings
    printf("thread_id (after barrier) = %d\n", thread_id);

  }
}
