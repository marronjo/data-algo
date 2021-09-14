#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>

//Joe Marron 18327262
//Part3 Assignment 2

#define ARRAY_SIZE 18627
#define STRING_SIZE 50

struct ign{
  char title[STRING_SIZE]; // x = 0
  char platform[STRING_SIZE];
  int score;
  int release; //x = 3
};

struct ign ign_array[ARRAY_SIZE];

void init(){
  for (int i = 0; i < ARRAY_SIZE; i++){
    ign_array[i].title[0] = '\n';
    ign_array[i].platform[0] = '\n';
    ign_array[i].score = 0;
    ign_array[i].release = 0;
  }
}

void selection_sort(){
  int min_index;
  int min_val = 11;

  for(int i = 1; i < ARRAY_SIZE - 1; i++){
    for(int j = i; j < ARRAY_SIZE - 1; j++){
      if(ign_array[j].score <= min_val){
        min_val = ign_array[j].score;
        min_index = j;
      }
      //printf(" %d ", j);
    }
    min_val = 11;
    if(min_index != i){
      //struct swap(ign_array[], min_index, i);
      struct ign temp = ign_array[min_index];
      ign_array[min_index] = ign_array[i];
      ign_array[i] = temp;
      //printf("\nswap no. %d\n", i);
    }
  }
}

void print_ign(){
  for(int i = 0; i < ARRAY_SIZE - 1; i++){
    printf("%s %s %d %d\n", ign_array[i].title, ign_array[i].platform, ign_array[i].score, ign_array[i].release);
  }
}

void print_top10(){
  int count = 1;
  printf("\n");
  for(int i = ARRAY_SIZE - 11; i < ARRAY_SIZE - 1; i++){
    printf("%d.\t%s %s %d %d\n", count, ign_array[i].title, ign_array[i].platform, ign_array[i].score, ign_array[i].release);
    count ++;
  }
}

void lower_case(char* buffer){
  for(int i = 0; i < sizeof(buffer); i++){
    buffer[i] = tolower(buffer[i]);
  }
}

char c;

int next_field(FILE *csv, char *buffer, int max_len){
  int count = 0;
  bool qmark = 0;

do{
    c = fgetc(csv);
    if (c == '"' && qmark == 0){
      qmark = 1;

    }
    else if(c == '"' && qmark == 1){
      qmark = 0;
    }

    if(qmark == 1 && c != '"'){
      buffer[count] = c;
      count++;
    }
    else{
      switch(c){
        case ',':
          buffer[count] = '\0';
          return 0;
          break;

        case '\n':
          buffer[count] = '\0';
          return 1;
          break;

        case EOF:
          return 1;
          break;

        case '"':
          buffer[count] = ' ';
          break;

        default:
          buffer[count] = c;
          count++;
          break;
      }
    }
  } while(count <= max_len);
  fclose(csv);
}


void insert(char *buffer, int i, int j){
  switch(i){
    case 0:
      strcpy(ign_array[j].title, buffer);
      break;
    case 1:
      strcpy(ign_array[j].platform, buffer);
      break;
    case 2:
      ign_array[j].score = atoi(buffer);
      break;
    case 3:
      ign_array[j].release = atoi(buffer); 
  }
}

int max = 100;
int condition;
int num = 0;
int x, y = 0;

int main(){

  //init();
  

  FILE *names;
  names = fopen("ign.csv", "r");

  if(names == NULL){
    printf("Error File Empty!");
  }
  else{

    char *fieldbuff;
    fieldbuff = (char*)malloc(max);

    while(!feof(names)){

      condition = next_field(names, fieldbuff, max);
      lower_case(fieldbuff);

      if(condition == 1){
        //printf("%s \n", fieldbuff);
        insert(fieldbuff, x, y);
        memset(fieldbuff, '\0', sizeof(fieldbuff));
        x = 0;
        y++;
      }
      else if(condition == 0){
        //printf("%s ", fieldbuff);
        insert(fieldbuff, x, y);
        memset(fieldbuff, '\0', sizeof(fieldbuff));
        x++;
      }
    }
  }
  fclose(names);
  
  selection_sort();
  print_top10();

  printf("\nProgram Complete\n");
  return 0;
}