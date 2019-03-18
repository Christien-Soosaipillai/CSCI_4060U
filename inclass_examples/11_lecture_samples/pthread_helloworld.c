#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5

void *hello_world(void *id);

int main() {
  //Declare threads
  pthread_t threads[NUM_THREADS];

  //Create threads
  for (long i=0; i<NUM_THREADS; i++) {
    printf("Creating thread %ld\n", i);

    /*
      Description:
        int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                                      void *(*start)(void *), void *arg);

        'thread' : Is the "LOCATION" where the ID of the newly created thread
                 should be stored, or NULL if the thread ID is not required.

        'attr' : Is the thread attribute object specifying the "ATTRIBUTES" for the
                thread that is being created. If attr is NULL, the thread is
                created with default attributes.

        'start' : Is the main function for the thread; the thread "BEGINS"
                  executing user code at this address.

        'arg' :  Is the "ARGUMENT" passed to "START".



     int pthread_create(pthread_t *thread,
                          const pthread_attr_t *attr,
                          void *(*start_routine) (void *),
                          void *arg);
    */
    int error = pthread_create(&threads[i], NULL,
                               hello_world, (void *)i);
    if (error) {
      printf("ERROR\n");
      exit(-1);
    }
  }
  //exit main threads
  pthread_exit(NULL);
}

void *hello_world(void *id) {
  long thread_id;
  thread_id = (long)id;
  printf("Hello world from thread %ld\n", thread_id);
  pthread_exit(NULL);
}
