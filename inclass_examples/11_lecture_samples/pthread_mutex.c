#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 5

struct thread_data {
  long thread_id;
  char value;
};

//shared data
int total=0;
//mutual exclusion variable
pthread_mutex_t mutex_total;

void *hello_world(void *threadarg);

int main() {
  struct thread_data thread_data_array[NUM_THREADS];

  //initializae mutex_total
  //to default values ~~ including unlocked
  pthread_mutex_init(&mutex_total, NULL);

  //Declare threads
  pthread_t threads[NUM_THREADS];
  //Declare thread attributes
  pthread_attr_t a;
  void *status; //used in join

  //initialize the thread attributes
  pthread_attr_init(&a); //set a to all default attributes
  pthread_attr_setdetachstate(&a, PTHREAD_CREATE_JOINABLE);

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
    int error = pthread_create(&threads[i], &a,
                               hello_world,
                               (void *)&thread_data_array[i]);
    if (error) {
      printf("ERROR: create()\n");
      exit(-1);
    }
  }
  //free attribute after using -- free up memory
  pthread_attr_destroy(&a);


  //after creation we need to join threads
  for (long i=0; i< NUM_THREADS; i++) {
    int error = pthread_join(threads[i], &status);
    if (error) {
        printf("ERROR: join()\n");
        exit(-1);
    }
  }

  printf("total = %d!\n",total);

  //destroy the mutex to release memory
  pthread_mutex_destroy(&mutex_total);

  //exit main threads
  pthread_exit(NULL);
}

void *hello_world(void *threadarg) {
  struct thread_data *my_data;
  my_data = (struct thread_data*)threadarg;

  printf("Request lock in thread %ld\n", my_data->thread_id);
  pthread_mutex_lock(&mutex_total);
  printf("Aquired lock in thread %ld\n", my_data->thread_id);
  sleep((int)my_data->value/7);
  total = total + (int)my_data->value;
  printf("Release lock in thread %ld\n", my_data->thread_id);
  pthread_mutex_unlock(&mutex_total);
  printf("Hello world %c from thread %ld\n",
         my_data->value, my_data->thread_id);
  pthread_exit(NULL);
}
