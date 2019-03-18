//==============================================================================
//C Code for pthread_create() test

//REAL TIME:0m0.916s
//CPU TIME:0m0.978s

//==============================================================================
#include <pthread.h>  //imlpements the POSIX thread libraries which is a standard based thread API for C/C++
#include <stdio.h>    //defines three variable types, several macros, and various functions for performing input and output.
#include <stdlib.h>   //defines four variable types, several macros, and various functions for performing general functions

#define NTHREADS 50000

void *do_nothing(void *null) {      //This function si given as a parameter for the
  int i;                            //pthread_create, known as the start routine.
  i=0;                              //This function just terminates the pthread.
  pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
  int rc, i, j, detachstate;
  pthread_t tid;                    //acts as a handle for the new thread
  pthread_attr_t attr;              //thread attributes object

  pthread_attr_init(&attr);         //initialize thread attributes object
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);  //set detachstate attribute

  for (j=0; j<NTHREADS; j++) {
    rc = pthread_create(&tid, &attr, do_nothing, NULL);         //starts a new thread in the calling process
    if (rc) {                                                   //If unsuccessful, pthread_create() returns -1, If successful, pthread_create() returns 0
      printf("ERROR; return code from pthread_create() is %d\n", rc);
      exit(-1);
    }

    rc = pthread_join(tid, NULL);                                   //Allows the calling thread to wait for the ending of the target thread
    if (rc) {                                                       //If successful, pthread_join() returns 0
      printf("ERROR; return code from pthread_join() is %d\n", rc); //If unsuccessful, pthread_join() returns -1
      exit(-1);                                                     //will exit code unsuccessfully
      }
    }

    pthread_attr_destroy(&attr);                                  //destroy thread attributes object
    pthread_exit(NULL);                                           //terminates the calling thread and returns a value

}
