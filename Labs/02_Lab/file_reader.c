#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>


#define MAXCHAR 1000
#define NUM_THREADS 8

char* getTopGrade(int i);

FILE* fp;                 //pointer to file
char* fileNames[] = {"CSCI4060U_Lab02_data/1.csv", "CSCI4060U_Lab02_data/2.csv",
                     "CSCI4060U_Lab02_data/3.csv", "CSCI4060U_Lab02_data/4.csv",
                     "CSCI4060U_Lab02_data/5.csv", "CSCI4060U_Lab02_data/6.csv",
                     "CSCI4060U_Lab02_data/7.csv", "CSCI4060U_Lab02_data/8.csv"};

int main(void){

  #ifdef _OPEMP
    omp_set_num_threads(NUM_THREADS);
  #endif



  char topStudents[omp_get_num_threads()];

  #pragma omp parallel
  {
    int thread_id;
    thread_id = omp_get_thread_num();
    topStudents[thread_id] = getTopGrade(thread_id);
    printf("%d\n", thread_id);
  }



  //array consists of 8 char pointers
  //each char consists of 8 bytes in memory
  //so you get 64 / 8 = 8;
  // for(int i = 0; i < sizeof(fileNames)/sizeof(char*); i++){
  //
  //
  //
  // }

  return 0;
}

char* getTopGrade(int i){

  printf("Reading from file #%d: %s\n", i+1, fileNames[i] );
  fp = fopen(fileNames[i],"r");
  if(fp == NULL){
    printf("Could not open file %s",fileNames[i]);
    return;
  }
  char line[MAXCHAR];

  char* hFirst = strdup("");    //returns a pointer to this string ""
  char* hLast = strdup("");
  char* hGpa = strdup("0.0");

  while(fgets(line, MAXCHAR, fp) != NULL){
    //printf("%s\n",line);
    //printf("current highest: %s, %s, %s", hFirst, hLast, hGpa);

    char* first = strtok(line, ",");
    char* last = strtok(NULL, ",");
    char* gpa = strtok(NULL,",");

    //printf("reading ooL: %s, %s, %s", first, last, gpa);

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
  //avoid memory leaks in our code
  fclose(fp);
  free(hFirst);
  free(hLast);
  free(hGpa);

  printf("highest graded student: %s, %s, %s\n", hFirst, hLast, hGpa);

  char* final = strdup("%s, %s, %s", hFirst, hLast, hGpa);    //returns a pointer to this string ""

  return final;

}
