#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <omp.h>
#include <math.h>

#define MAXCHAR 2000
#define NUM_THREADS 2
#define MAX_AMOUNT 10

double longitude[10];
double latitude[10];

/*
Thread 1:
  -real	0m0.024s
  -user	0m0.000s
  -sys	0m0.017s

Thread 2:
  -real	0m0.035s
  -user	0m0.027s
  -sys	0m0.024s

Thread 4:
  -real	0m0.035s
  -user	0m0.027s
  -sys	0m0.024s

Thread 8:
  -real	0m0.122s
  -user	0m0.019s
  -sys	0m0.094s

*/


int front  = 0;
char* fileNames[] = {"latitude.csv","longitude.csv"};
FILE* fp;                 //pointer to file

void readFile(int i);

int main(){

  for(int i = 0; i < sizeof(fileNames)/sizeof(char *); i++){
    readFile(i);

  }

  return 0;
}

void readFile(int i){


  fp = fopen(fileNames[i],"r");
  char line[MAXCHAR];

  //printf("Reading file %s",fileNames[i]);


  //If file can't be read
  if(fp == NULL){
    printf("Could not open file %s","latitude.csv");
    return;
  }

  int id,nthrds;
  omp_set_num_threads(NUM_THREADS);

  //read the files
  while(fgets(line, MAXCHAR, fp) != NULL){

    //get data check if array is full
    if(front != 10){

      //if array isnt full add data
      latitude[front] = atof(line);
      front++;
    }else{
      id = omp_get_thread_num();
      nthrds = omp_get_num_threads();
      #pragma omp parallel
      {

        for(int i = id; i < sizeof(latitude)/ sizeof(char*); i=i+nthrds){

          int degree, minutes, seconds;
          if(i < 10){
            if(latitude[i] < 0.0){
              degree = (int)ceil(latitude[i]);
              minutes = (int)abs(ceil((latitude[i]-degree) * 60));
              seconds = (int)ceil((((latitude[i]-degree) * 60)-floor((latitude[i]-degree) * 60)) * 60 );
            }else{
              degree = (int)floor(latitude[i]);
              minutes = (int)abs(floor((latitude[i]-degree) * 60));
              seconds = (int)ceil((((latitude[i]-degree) * 60)-floor((latitude[i]-degree) * 60)) * 60 );
            }
          }
          printf("%i Degrees, %i', %i\"\n", degree, minutes, seconds);
        }
      }
      // for(int i = 0; i < sizeof(latitude)/ sizeof(char*); i++){
      //
      //   int degree, minutes, seconds;
      //   if(latitude[i] < 0.0){
      //     degree = (int)ceil(latitude[i]);
      //     minutes = (int)abs(ceil((latitude[i]-degree) * 60));
      //     seconds = (int)ceil((((latitude[i]-degree) * 60)-floor((latitude[i]-degree) * 60)) * 60 );
      //   }else{
      //     degree = (int)floor(latitude[i]);
      //     minutes = (int)abs(floor((latitude[i]-degree) * 60));
      //     seconds = (int)ceil((((latitude[i]-degree) * 60)-floor((latitude[i]-degree) * 60)) * 60 );
      //   }
      //   //printf("%i Degrees, %i', %i\"\n", degree, minutes, seconds);
      // }


      #pragma omp critical
      {
        front = 0;
        latitude[front] = atof(line);
        front++;
      }
    }
    //printf("Reading from file: %s\n",line);

  }
  fclose(fp);

}
