#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5

struct thread_data {

  long thread_id;
  char value;

};

struct thread_data thread_data_array[NUM_THREADS];

void *hello_world(void *threadArg);

int main() {
  //Declare threads
  pthread_t threads[NUM_THREADS];

  //Create threads
  for (long i=0; i<NUM_THREADS; i++) {
    thread_data_array[i].thread_id = i;
    thread_data_array[i].value = (char)(i+65);
    printf("Creating thread %ld\n", i);

    /*  int pthread_create(pthread_t *thread,
                          const pthread_attr_t *attr,
                          void *(*start_routine) (void *),
                          void *arg);
    */
    int error = pthread_create(&threads[i], NULL,
                               hello_world, (void *)&thread_data_array[i]);
    if (error) {
      printf("ERROR\n");
      exit(-1);
    }
  }
  //exit main threads
  pthread_exit(NULL);
}

void *hello_world(void *threadArg) {
  struct thread_data *my_data;
  my_data = (struct thread_data*)threadArg;
  printf("Hello world %c from thread %ld\n", my_data ->value, my_data->thread_id);
  pthread_exit(NULL);
}
