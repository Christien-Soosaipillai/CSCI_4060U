#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 1
static long num_steps = 10000000;
double step;

/////////////////////////////////////////////////////

/* PURPOSE OF PROGRAM
Parallelization of the serial pi program using the
parallel directive and a parallel for loop (with a reduction).
*/

////////////////////////////////////////////////////

int main() {
  double x;
  double pi = 0.0; //shared variable accessed by all threads in a critical region
  double sum =0.0;
  int thread_count;

  //change in x (i.e. width of rectangle)
  step = 1.0/(double)num_steps;

  omp_set_num_threads(NUM_THREADS);

  #pragma omp parallel
  {
    double x;

    //Calculate the summnation of F(x)
    //i.e. the sum of rectangles
    //(to approximate pi)
    #pragma omp for reduction (+:sum)
    for (int i=0; i < num_steps; i++) {
      //calculate height
      x = (i+0.5)*step;
      sum = sum + 4/(1.0+x*x); //sum F(x)
    }


  }
  pi = step * sum;
  printf("pi = %f", pi);
}
