//==============================================================================
//C Code for fork() creation test

//REAL TIME: 0m3.992s
//CPU TIME: 0m4.085s

//==============================================================================
#include <stdio.h>    //defines three variable types, several macros, and various functions for performing input and output.
#include <stdlib.h>   //defines four variable types, several macros, and various functions for performing general functions
#include <unistd.h>   //provides access to the POSIX operating system API
#include <sys/types.h>//defines a collection of typedef symbols and structures

#define NFORKS 50000

void do_nothing() {           //literally does nothing in this code
  int i;
  i= 0;
}

int main(int argc, char *argv[]) {
  int pid, j, status;
  pid_t processID;

  for (j=0; j<NFORKS; j++) {          //for the number of processes
    if ((processID = fork()) < 0 ) {  //if the processes ID, returned by fork(creates a child process runs concurrently with process ), is less than 0
                                      //creates a
      printf ("fork failed with error code= %d\n", processID);  //print an error code
      exit(0);                      //terminate the program (successful termination)
    }
    else if (processID ==0) {       //if processID is 0 do absolutly nothing
      do_nothing();
      exit(0);                      //terminate the program (successful termination)
    }
    else {
      waitpid(processID, &status, 0); //suspends the calling process
      }                                //until the system gets status information on the child of processID
    }
  }                                     /*If pid is greater than 0, waitpid() waits for termination of the specific child whose process ID is equal to pid.
                                        If pid is equal to zero, waitpid() waits for termination of any child whose process group ID is equal to that of the caller.
                                        If pid is -1, waitpid() waits for any child process to end.
                                        If pid is less than -1, waitpid() waits for the termination of any child whose process group ID is equal to the absolute value of pid.
                                        */
