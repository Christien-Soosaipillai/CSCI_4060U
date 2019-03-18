#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5

struct thread_data {
  long thread_id;
  char value;
};

void *hello_world(void *threadarg);

int main() {
  struct thread_data thread_data_array[NUM_THREADS];

  //Declare threads
  pthread_t threads[NUM_THREADS];
  //Declare thread attributes
  pthread_attr_t a;
  void *status; //used in join

  //initialize the thread attributes
  pthread_attr_init(&a); //set a to all default attributes
  pthread_attr_setdetachstate(&a, PTHREAD_CREATE_DETACHED);

  /*PTHREAD_CREATE_DETACHED
              Threads that are created using attr will be created in a
              detached state.

    PTHREAD_CREATE_JOINABLE
              Threads that are created using attr will be created in a
              joinable state.


          "Joinable" : means that the thread's creator is still responsible for
          the thread's resources; you must join the thread at some point to wait
          for the thread to finish (if it hasn't already) and clean up those resources.

          "Detached" : means that the thread has been made responsible for its own
          resources, and must not be joined. Do this if you want to let the thread
          run independently and forget about it.

  */

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
  //free attribute after using
  pthread_attr_destroy(&a);


  //after creation we need to join threads, however
  //since we are using detach we dont have to
/*  for (long i=0; i< NUM_THREADS; i++) {
    int error = pthread_join(threads[i], &status);
    if (error) {
        printf("ERROR: join()\n");
        exit(-1);
    }
  }
*/
  printf("main thread complete and no join done!\n");
  //exit main threads
  pthread_exit(NULL);
}

void *hello_world(void *threadarg) {
  struct thread_data *my_data;
  my_data = (struct thread_data*)threadarg;
  printf("Hello world %c from thread %ld\n",
         my_data->value, my_data->thread_id);
  pthread_exit(NULL);
}
