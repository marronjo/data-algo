#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//Joe Marron 18327262
//Part3 Assignment 0

int next_field(FILE *csv, char *buffer, int max_len);

char c;
int condition, end;

int main(){

  int max = 200;

  FILE *pokemon;
  pokemon = fopen("pokemon.csv", "r");

  if(pokemon == NULL){
    printf("Error File Empty!");
  }
  else{

    char *fieldbuff;
    fieldbuff = (char*)malloc(max);

    while(!feof(pokemon)){

      condition = next_field(pokemon, fieldbuff, max);

     if(condition == 1){
        printf("%s  ", fieldbuff);
        printf("\n");
        printf("\n");
        memset(fieldbuff, '\0', sizeof(fieldbuff));
      }
      else if(condition == 0){
        printf("%s  ", fieldbuff);
        printf("\n");
        memset(fieldbuff, '\0', sizeof(fieldbuff));
      }
    }
  }
  fclose(pokemon);
  printf("Done");
  return 0;
}

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
