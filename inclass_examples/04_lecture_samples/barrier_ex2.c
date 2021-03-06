#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#ifdef _OPENMP
  #include <omp.h>
#else
  #define omp_get_num_threads() 1
  #define omp_get_thread_num() 0
#endif

#define NUM_THREADS 4

int calcGrade(int i);
int calcOtherAvg(int i, int *g);

/////////////////////////////////////////////////////

/* PURPOSE OF PROGRAM
A more detailed example of parallelization using a
barrier to separate two calculations involving grades.
*/

/////////////////////////////////////////////////////

int main() {
  #ifdef _OPENMP
    omp_set_num_threads(NUM_THREADS);
  #endif
  int Grades[omp_get_num_threads()];
  int Averages[omp_get_num_threads()];

  #pragma omp parallel
  {
    int thread_id;
    thread_id = omp_get_thread_num();
    Grades[thread_id] = calcGrade(thread_id);

    //we put the barrier here so we can wait for
    //all the grades to be calculated first, if we
    //don't wait then are going to get messed up values
    //when we calculate the Averages[thread_id] 
    #pragma omp barrier
    Averages[thread_id] = calcOtherAvg(thread_id, Grades);
    //printf ("Student %d\tGrade %d\tAverage %d\n",
    //        thread_id+1, Grades[thread_id], Averages[thread_id]);
  }
}

//returns a random grade
int calcGrade(int i) {
  srand(time(NULL));
  /*for (int j = 0; j < i; j++) {
    rand();
  }*/
  return (rand()%101);
}

//
int calcOtherAvg(int i, int *g) {
  float sum = 0;
  printf("entering loop for thread %i\n",i+1);
  for (int j=0; j < omp_get_num_threads(); j++) {
    if (j != i) {
      printf("value in calcOtherAvg: %i\n",g[j]);
      sum += g[j];
    }
  }
  if (omp_get_num_threads() > 1) {
    return (sum/(omp_get_num_threads()-1));
  } else {
    return 0;
  }
}
