#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 8

/////////////////////////////////////////////////////

/* PURPOSE OF PROGRAM
An example of parallelizing a serial loop by first
modifying the loop to ensure all iterations are independent.
*/

////////////////////////////////////////////////////

int main() {

  int i;
  double result[NUM_THREADS];

  #pragma omp for
  {
    for (i = 0; i < NUM_THREADS; i++) {
        int j = 5 + 2*(i+1);
        result[i] = 5*6*7 +j;
        printf ("result for iteration %d is %f\n",
                i, result[i]);
    }
  }
  return 0;
}
