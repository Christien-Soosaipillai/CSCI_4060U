#include <stdio.h>
#include <omp.h>

static long num_steps = 50;
double step;

double pi;
int iterator = 0;

//double output(int ID);

int main() {

  omp_set_num_threads(2);


  //change in x (i.e. width of rectangle)
  step = 1.0/(double)num_steps;

  double sum[2];
  #pragma omp parallel
  {
    double x;
    int threadID = omp_get_thread_num();

    printf("starting thread %d calculations...\n ", threadID);

    //number starts at what the previous function ended at
    //if first function running it starts as 0
    //if the number is less than current
    sum[threadID] = 0.0;
    for(int i = 0; i < num_steps/omp_get_num_threads()+1; i++) {

      //Here is my logic for the for loop
      //first thread = ((100 steps/2)* thread id 0) + i = 1....2....3
      //second thread = ((100 steps/2)* thread omp_get_num_threads()id 1) + i = 51....52....53
      double formula = ((num_steps/omp_get_num_threads()+1)*(threadID))+(double)i;
      printf("i =  %ld \n", (num_steps/omp_get_num_threads()+1)*(threadID));

      x = (formula*0.5)*step;
      sum[threadID] += 4/(1.0+x*x); //sum F(x)
    }
    printf("Thread %d is finished \n", threadID);
  }
  for(int j = 0; j < omp_get_num_threads(); j++){
    pi = step * sum[j];
  }
  printf("pi = %f \n", pi);

  return 0;
}
