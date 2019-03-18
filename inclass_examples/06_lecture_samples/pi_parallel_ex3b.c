#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 8
static long num_steps = 10000000;
double step;

/////////////////////////////////////////////////////

/* PURPOSE OF PROGRAM
The danger of placing critical regions in loops is
demonstrated in this program. This is not a best practice
*/

////////////////////////////////////////////////////

int main() {
  double x;
  double pi = 0.0; //shared variable accessed by all threads in a critical region
  int thread_count;

  //change in x (i.e. width of rectangle)
  step = 1.0/(double)num_steps;

  omp_set_num_threads(NUM_THREADS);

  #pragma omp parallel
  {
    int thread_id;
    int t_count;
    double x;

    thread_id = omp_get_thread_num();
    t_count = omp_get_num_threads();

    //calculate the summation of F(x)
    // (i.e. sum of rectangles)
    //in the approximation of pi
    for (int i=thread_id; i < num_steps; i = i + t_count) {
      //calculate height
      x = (i+0.5)*step;
      #pragma omp critical
      {
        //sum F(x), This is dangerous because every thread has to wait
        //for the lock to be released before updating pi resulting in
        //lots of overhead.
        pi += 4/(1.0+x*x); 
      }
    }
  }
  pi *= step;
  printf("pi = %f", pi);
}
