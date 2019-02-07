#include <stdio.h>
#ifdef _OPENMP
  #include <omp.h>
#else
  #define omp_get_num_threads() 1
  #define omp_get_thread_num() 0
#endif

#define NUM_THREADS 16

int calcGrade(int threadID);
int calcAverage(int i, int *grades);

int A[NUM_THREADS];
int iterator = 0;

int main(){
  #ifdef _OPENMP
    omp_set_num_threads(NUM_THREADS);
  #endif
  int Grades[omp_get_num_threads];
  int Averages[omp_get_num_threads];


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
    Grades[thread_id] = calcGrade(thread_id);

    #pragma omp barrier
    //Call calc 2(thread ID, A) and store result in array b[thread_ID]
    Averages[thread_id] = calcAverage(thread_id, Grades);
    printf ("student %d\tGrade %d\%\t", thread_id, Grades[thread_id]) 
  }
}

int calcGrade(int i){
  srand(time(NULL));
  for(int j = 0; j < i; j++){
    rand();
  }
  return (rand()%101);
}


int calcAverage(int i, int *g){
  int sum = 0;
  for(int  j = 0; j < omp_get_num_threads(); j++){
      if(j != i){
        sum += g[j];
      }
  }
  if(omp_get_num_threads() > 1){
    return
  }
  return (sum/ (omp_get_num_threads()-1))


}
