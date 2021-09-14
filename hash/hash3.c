#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define ARRAY_SIZE 67
#define MAX_STRING_SIZE 25
#define COEF 29

struct hash{
  char name[MAX_STRING_SIZE];
  int frequency;
};

int next_field(FILE *csv, char *buffer, int max_len);
int hash1(char *s);
int hash2(char *s);
int hash3(char* s);
void insert_hash(char *buffer, int hash_val, int hash_val2, int *collide);
void print_table();
void init();
void lower_case(char *buffer);

char c;
int condition;
const int max = 1000;
struct hash hash_table[ARRAY_SIZE];

int main(){

  int index, index2;
  int collision = 0;
  int num = 0;
  char *input;
  int equalcount = 0;
  input = (char*)malloc(20);
  init();

  FILE *names;
  names = fopen("names.csv", "r");

  if(names == NULL){
    printf("Error File Empty!");
  }
  else{

    char *fieldbuff;
    fieldbuff = (char*)malloc(max);

    while(!feof(names)){

      condition = next_field(names, fieldbuff, max);
      lower_case(fieldbuff);
      index = hash2(fieldbuff);
      index2 = hash3(fieldbuff);

      if(condition == 1){
        //printf("%s --> %u\n", fieldbuff, index);
        insert_hash(fieldbuff, index, index2, &collision);
        memset(fieldbuff, '\0', sizeof(fieldbuff));
      }
      else if(condition == 0){
        //printf("%s --> %u\n", fieldbuff, index);
        insert_hash(fieldbuff, index, index2, &collision);
        memset(fieldbuff, '\0', sizeof(fieldbuff));
      }
      num++;
    }
  }
  fclose(names);

  float load = 0;
  float num_terms = num;
  float array = ARRAY_SIZE;
  load = 100*(num_terms/array);

  printf("\nCapacity:\t%d\n", ARRAY_SIZE);
  printf("Num Terms:\t%d\n", num);
  printf("Collisions:\t%d\n", collision);
  printf("Load:\t%f%%\n", load);

  printf("Enter term to get frequency or \"quit\" to escape: ");
  scanf("%[^\n]%*c", input);
  while(strcmp(input, "quit") != 0){
    equalcount = 0;
    int summup = 0;
    for(int q = 0; q < ARRAY_SIZE; q++){
      if(strcmp(hash_table[q].name, input) == 0){
        summup+= hash_table[q].frequency;
        equalcount = 1;
      }
    }
    printf("\n>>>\t%d\n", summup);
    if(equalcount != 1){
      printf("%s does not exist \n", input);
    }
    printf("\n>>>\t");
    scanf("%[^\n]%*c", input);

  }

  //print_table();
  printf("\nProgram Complete\n");
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

int hash2(char* s){//basic hash function
  int hash = 0;
  while(*s){
    hash = (hash + *s) % ARRAY_SIZE;
    s++;
  }
  return hash;
}

int hash3(char *s){
  int h = 0;
  while(*s){
    h = (COEF*h + *s) % (ARRAY_SIZE-1); //a prime coefficient to reduce collisions
    s++;
  }
  h++; //sinze % arraysize-1 will leave the entry at array_size empty I add 1 to h at the end
  return h;
}

void init(){
  for (int i = 0; i < ARRAY_SIZE; i++){
    hash_table[i].name[0] = '\n';
    hash_table[i].frequency = 0;
  }
}

void print_table(){
  for(int i = 0; i < ARRAY_SIZE; i++){
    if(hash_table[i].name[0] == '\n'){
      printf("\t%d\t----\n", i);
    }
    else{
      printf("\t%d %s %d\n", i, hash_table[i].name, hash_table[i].frequency);
    }
  }
}

void lower_case(char *buffer){
  for (int k = 0; buffer[k] != '\0'; k ++){
    buffer[k] = tolower(buffer[k]);
  }
}

void insert_hash(char *buffer, int hash_val, int hash_val2, int *collide){
  if(strcmp(hash_table[hash_val].name, buffer) == 0){
    hash_table[hash_val].frequency += 1;
  }
  else if(hash_table[hash_val].name[0] != '\n' && buffer != ""){
    //*collide += 1;
    int k = 0;
    int i = 1;
    int double_hash;
    while(k == 0){
      double_hash = (hash_val + i*hash_val2) % ARRAY_SIZE;//double hashing formula
      if(hash_table[double_hash].name[0] == '\n'){
        strcpy(hash_table[double_hash].name, buffer);
        hash_table[double_hash].frequency += 1;
        k = 1;
      }
      *collide += 1;
      i++;
    }
  }
  else if(hash_table[hash_val].name[0] == '\n'){
    strcpy(hash_table[hash_val].name, buffer);
    hash_table[hash_val].frequency += 1;
  }
}
