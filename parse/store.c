#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//Joe Marron 18327262
//Part4 Assignment 0

typedef struct Storage{
  int number;
  char *name;
  char *type1;
  char *type2;
  int  total;
  int  hp;
  int  attack;
  int  defense;
  int  spattack;
  int  spdefense;
  int  speed;
  int  generation;
  char *legendary;
  char *pokedex;
} storage;

int next_field(FILE *csv, char *buffer, int max_len);
void store_data(char *buffer, int x_value, int y_value, storage *storage);

char c;
int condition, end, count, x_value, y_value;
int max_val, subtotal = 0;
float average;

const int max = 1000;

int main(){

  struct Storage s[1000];
  int x, y = 0;

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
        store_data(fieldbuff, x, y, s);
        y++;
        x = 0;
        printf("%s  ", fieldbuff);
        printf("\n");
        printf("\n");
        memset(fieldbuff, '\0', sizeof(fieldbuff));
      }
      else if(condition == 0){
        store_data(fieldbuff, x, y, s);
        x++;
        printf("%s  ", fieldbuff);
        printf("\n");
        memset(fieldbuff, '\0', sizeof(fieldbuff));
      }
    }
  }

  fclose(pokemon);
  for(int i = 1; i < 650; i++){
    if(s[i].defense > max_val){
      max_val = s[i].defense;
    }
    subtotal += s[i].defense;
  }
  average = subtotal/649;

  printf("sum of ds: %d\n", subtotal);
  printf("The best defense strength is: %d\n", max_val);
  printf("The average defense strength is: %f\n", average);
  printf("\nTasks Complete\n");
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

void store_data(char *buffer, int x_value, int y_value, storage *storage){

  switch(x_value){
    case 0:
    storage[y_value].number = atoi(buffer);
    break;

    case 1:
    storage[y_value].name = buffer;
    break;

    case 2:
    storage[y_value].type1 = buffer;
    break;

    case 3:
    storage[y_value].type2 = buffer;
    break;

    case 4:
    storage[y_value].total = atoi(buffer);
    break;

    case 5:
    storage[y_value].hp = atoi(buffer);
    break;

    case 6:
    storage[y_value].attack = atoi(buffer);
    break;

    case 7:
    storage[y_value].defense = atoi(buffer);
    break;

    case 8:
    storage[y_value].spattack = atoi(buffer);
    break;

    case 9:
    storage[y_value].spdefense = atoi(buffer);
    break;

    case 10:
    storage[y_value].speed = atoi(buffer);
    break;

    case 11:
    storage[y_value].generation = atoi(buffer);
    break;

    case 12:
    storage[y_value].legendary = buffer;
    break;

    case 13:
    storage[y_value].pokedex = buffer;
    break;
  }
}
