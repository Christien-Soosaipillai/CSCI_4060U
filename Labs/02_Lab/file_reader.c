#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <omp.h>


#define MAXCHAR 1000
#define NUM_THREADS 2

char getTopGrade(int i);

FILE* fp;                 //pointer to file
char* fileNames[] = {"CSCI4060U_Lab02_data/1.csv", "CSCI4060U_Lab02_data/2.csv",
                     "CSCI4060U_Lab02_data/3.csv", "CSCI4060U_Lab02_data/4.csv",
                     "CSCI4060U_Lab02_data/5.csv", "CSCI4060U_Lab02_data/6.csv",
                     "CSCI4060U_Lab02_data/7.csv", "CSCI4060U_Lab02_data/8.csv"};

int main(void){


  omp_set_num_threads(NUM_THREADS);

  char topStudents[sizeof(fileNames)/sizeof(char*)];

  #pragma omp parallel
  {
    //returns the number of threads in the team currently
    //executing the parallel region from which it is called.
    // The function binds to the closest enclosing PARALLEL directive
    printf("Number of threads: %i\n", omp_get_num_threads());

    int thread_id, t_count;
    thread_id = omp_get_thread_num();
    t_count = omp_get_num_threads();
    int files_handled = sizeof(fileNames)/sizeof(char*);
    for(int i = thread_id; i < files_handled;i = i + t_count){
      topStudents[i] = getTopGrade(i);
    }

    #pragma omp barrier
    // for(int i = 0; i < sizeof(topStudents); i++){
    //   printf("result at position %i: %c\n", i, topStudents[i]);
    //
    // }
  }

  //array consists of 8 char pointers
  //each char consists of 8 bytes in memory
  //so you get 64 / 8 = 8;
  // for(int i = 0; i < sizeof(fileNames)/sizeof(char*); i++){

  return 0;
}

char getTopGrade(int i){

  //printf("Reading from file #%d: %s\n", i+1, fileNames[i] );
  fp = fopen(fileNames[i],"r");
  if(fp == NULL){
    printf("Could not open file %s",fileNames[i]);
    return 0;
  }
  char line[MAXCHAR];

  char *hFirst = strdup("");    //returns a pointer to this string ""
  char *hLast = strdup("");
  char *hGpa = strdup("0.0");

  while(fgets(line, MAXCHAR, fp) != NULL){

    char *first = strtok(line, ",");
    char *last = strtok(NULL, ",");
    char *gpa = strtok(NULL,",");

    double numGpa = atof(gpa);
    double numHGpa = atof(hGpa);

    //printf("gpa read: %f ++++++ gpa current: %f\n",numGpa, numHGpa );

    if(numGpa > numHGpa){

      //free our memory associated with the "h" variables
      free(hFirst);
      free(hLast);
      free(hGpa);

      //assign hFirst a pointer which points to the location of first
      hFirst = strdup(first);
      hLast = strdup(last);
      hGpa = strdup(gpa);

      //printf("after assignment: %s, %s, %s\n", hFirst, hLast, hGpa);
    }

  }

  printf("highest graded student from file %i: %s, %s, %s\n", i+1, hFirst, hLast, hGpa);

  //char *final = strdup("%s, %s, %s", hFirst, hLast, hGpa);    //returns a pointer to this string ""
  char final[100];
  strcpy(final, hFirst);
  strcpy(final, hLast);
  strcpy(final, hGpa);

  //avoid memory leaks in our code
  fclose(fp);
  free(hFirst);
  free(hLast);
  free(hGpa);

  return *final;

}
