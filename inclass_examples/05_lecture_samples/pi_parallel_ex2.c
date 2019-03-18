#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 2
#define PAD 8
//Padding is necessary due to cache line size (64 bytes)
//It prevents "false sharing" -- when data elements on the same
//line are copied back and forth between cores/threads
//This happens wityhj arrays because the elements are store contiguously
static long num_steps = 1000000;
double step;

/////////////////////////////////////////////////////

/* PURPOSE OF PROGRAM
improving the performance of pi_parallel_v1.c.
The original program suffers from “false sharing” between
array elements on the same cache line making the program make unwanted
copies. This program uses an architecture specific
solution (padding) to solve the problem.
*/

/////////////////////////////////////////////////////

int main() {
  double x;
  double pi;
  double sum[NUM_THREADS][PAD];
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
    if (thread_id == 0) {
      thread_count = t_count;
    }
    //calculate the summation of F(x)
    // (i.e. sum of rectangles)
    //in the approximation of pi
    sum[thread_id][0]=0.0;


    //order of for loop:
    //1st: initialize i = thread_id
    //2nd: if the condition is satisfied we enter the for loop
    //3rd: finally we do the increment step after entering the loop

    for (int i=thread_id; i < num_steps; i = i + t_count) {
      //calculate height

      //printf("thread id[%i]value of i = %i\n", thread_id, i);

      x = (i+0.5)*step;
      sum[thread_id][0] = sum[thread_id][0] + 4/(1.0+x*x); //sum F(x)
    }
  }

  pi=0.0;
  for (int i=0; i < thread_count; i++) {
    pi += step * sum[i][0];

  }
  printf("pi = %f", pi);
}
