#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAXCHAR 1000


char* fileNames[] = {"latitude.csv", "longitude.csv"};
FILE* fp;                 //pointer to file

int main(){

  for(int i = 0; i < sizeof(fileNames)/sizeof(char *); i++){
    fp = fopen(fileNames[i],"r");
    char line[MAXCHAR];

    //If file can't be read
    if(fp == NULL){
      printf("Could not open file %s","latitude.csv");
      return 0;
    }

    printf("Reading file %s\n",fileNames[i]);
    while(fgets(line, MAXCHAR, fp) != NULL){

    }
    fclose(fp);

  }
  return 0;
}
