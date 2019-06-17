#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 5

struct thread_data {
  int thread_id;
  int value;
};

int total; //shared data
pthread_mutex_t mutextotal; //mutual exclusion variable for total

struct thread_data thread_data_array[NUM_THREADS];

void *hello_world(void *threadarg);

int main () {
  //Declaring threads
  pthread_t threads[NUM_THREADS];
  //Declare thread attribute
  pthread_attr_t a;
  long i;
  int error;
  void *status; //used in join
  total = 0;

  //set mutex to default values including unlocked state
  pthread_mutex_init(&mutextotal, NULL);

  //initialize the thread attribute
  pthread_attr_init(&a); //set a to all default attributes
  pthread_attr_setdetachstate(&a, PTHREAD_CREATE_JOINABLE);

  //Creating threads
  for (i=0; i< NUM_THREADS; i++) {
    thread_data_array[i].thread_id = i;
    thread_data_array[i].value = 10 * (int)i;
    printf("Creating thread %ld\n", i);
    //pthread definition:
    //  int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
    //                    void *(*start_routine) (void *), void *arg);

    error = pthread_create(&threads[i], &a, hello_world,
                          (void *) &thread_data_array[i]);
    if (error) {
      printf("ERROR: create() %d\n", error);
      exit(-1);
    }
  }
  //free attribute after using
  pthread_attr_destroy(&a);
  //after creation need to add join
  for (i=0; i< NUM_THREADS; i++) {
    error = pthread_join(threads[i], &status);
    if (error) {
      printf("ERROR: join() %d\n", error);
      exit(-1);
    }
  }
  printf("Threads complete and join done!\n");
  printf("The total of all the values is %d\n", total);
  //destroy mutex
  pthread_mutex_destroy(&mutextotal);
  //exit main thread
  pthread_exit(NULL);
}

void *hello_world(void *threadarg) {
  int try_error;
  struct thread_data *my_data;
  my_data = (struct thread_data*) threadarg;
  printf("Request lock in thread %d\n", my_data->thread_id);
  try_error = pthread_mutex_trylock(&mutextotal);
  //printf("try_error = %d", try_error);
  if (try_error != 0) {
    printf("ERROR: trylock() %d in thread %d\n",
            try_error, my_data->thread_id);
  } else {
    printf("Acquired lock in thread %d\n", my_data->thread_id);
  /*  if (my_data->value == 10) {
      sleep(15);
    }*/
    total += my_data->value;
    printf("Release lock in thread %d\n", my_data->thread_id);
    pthread_mutex_unlock(&mutextotal);
  }
  printf("Hello world from thread %d! My value is %d\n",
        my_data->thread_id, my_data->value);
  pthread_exit(NULL);
}
