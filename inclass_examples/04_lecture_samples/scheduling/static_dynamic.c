#include <unistd.h>
#include <stdlib.h>
#include <omp.h>
#include <stdio.h>
#define THREADS 4
#define N 16
int main () {
  int i;
  #pragma omp parallel for schedule(static, 7) num_threads(THREADS) //static
  //#pragma omp parallel for schedule(dynamic) num_threads(THREADS) //dynamic
  for (i = 0; i < N; i++) {
  /* wait for i seconds */
    sleep(i);
    printf("Thread %d has completed iteration %d.\n",
    omp_get_thread_num( ), i);
  }
  /* all threads done */
  printf("All done!\n");
  return 0;
}
