#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 50

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

  /*
    'mutex' : The address of the variable to contain a mutex object.
    'attr' : The address of the variable containing the mutex attributes object.

  */

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

    /*
    1st ~ 'thread' : Is the thread to wait for
    2nd ~ 'status' : Is the location where the exit status of the joined thread is stored.
                     This can be set to NULL if the exit status is not required.

    */

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
  struct thread_data *my_data;
  my_data = (struct thread_data*) threadarg;
  pthread_mutex_lock(&mutextotal);                //aquire the lock
  total += my_data->value;
  pthread_mutex_unlock(&mutextotal);              //release the lock
  pthread_exit(NULL);
}
