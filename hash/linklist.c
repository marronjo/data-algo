#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define ARRAY_SIZE 55
#define COEF 31

typedef struct Node Node;
struct Node{
  //char *hash;
  char *person;
  char *deposition;
  char *surname;
  char *forename;
  char *age;
  char *type;
  Node* next;
};

struct temp{
  char *person;
  char *deposition;
  char *surname;
  char *forename;
  char *age;
  char *type;
};

int next_field(FILE *csv, char *buffer, int max_len);
int hash2(char *s);
int hash3(char* s);
void insert_hash(char *buffer, int col, struct temp *p);
void init();
void add_node(Node** list, int columnnum, int hashindex);
int search();
void insert_hash_table(int hash_value, int hash_value2);
void print_table();
void clear_temp();

char c;
int condition;
const int max = 1000;
//struct temp hash_table_temp[ARRAY_SIZE];
//struct temp hash_table_temp[2];
struct Node hash_table[ARRAY_SIZE];
int line, column = 0;

int main(){

  int index, index2;
  int collision = 0;
  int num = 0;
  char *input;
  int equalcount = 0;
  input = (char*)malloc(20);
  init();

  FILE *names;
  names = fopen("truncated.csv", "r");

  if(names == NULL){
    printf("Error File Empty!");
  }
  else{

    char *fieldbuff;
    fieldbuff = (char*)malloc(max);

    struct temp* hash_table_temp = malloc(sizeof(*hash_table_temp));

    //printf("malloc");
    //struct Node* hash_table = malloc(sizeof(hash_table));
    //printf("malloc done");

    while(!feof(names)){

      Node* head = NULL;

      condition = next_field(names, fieldbuff, max);

      if(condition == 1){ //end of line
        insert_hash(fieldbuff, column, hash_table_temp);
        memset(fieldbuff, '\0', sizeof(fieldbuff));
        column = 0;
        clear_temp();
      }

      else if(condition == 0){ // comma, eg new column
        insert_hash(fieldbuff, column, hash_table_temp);
        memset(fieldbuff, '\0', sizeof(fieldbuff));
        column++;
      }
      num++;
    }
  }
  fclose(names);

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
    h = (COEF*h + *s) % ARRAY_SIZE; //a prime coefficient to reduce collisions
    s++;
  }
  return h;
}

void init(){ //initialise everything in struct to 0 or \n
  for (int i = 0; i < ARRAY_SIZE; i++){
    hash_table[i].person = " ";
    hash_table[i].deposition = " ";
    hash_table[i].surname = " ";
    hash_table[i].forename = " ";
    hash_table[i].age = " ";
    hash_table[i].type = " ";
  }
}
/*
void add_node(Node** list, int columnnum, int hashindex){//adding values to node
    Node* newNode = (Node*)malloc(sizeof( Node ));
      newNode->person = hash_table_temp[1].person;
      newNode->deposition = hash_table_temp[1].deposition;
      newNode->surname = hash_table_temp[1].surname;
      newNode->forename = hash_table_temp[1].forename;
      newNode->age = hash_table_temp[1].age;
      newNode->type = hash_table_temp[1].type;
      newNode->next = *list;
      *list=newNode;
}*/

void insert_hash(char *buffer, int col, struct temp *p){
  if(col == 0){
    p->person = buffer;
    printf("%s  ", p->person);
  }
  if(col == 1){
    p->deposition = buffer;
    printf("%s  ", p->deposition);
  }
  if(col == 2){
    p->surname = buffer;
    printf("%s  ", p->surname);
  }
  if(col == 3){
    p->forename = buffer;
    printf("%s  ", p->forename);
  }
  if(col == 4){
  p->age = buffer;
  printf("%s  ", p->age);
  }
  if(col == 5){
    p->type = buffer;
    printf("%s\n", p->type);
  }
  else{
    printf(" ");
  }
}
/*
void insert_hash_table(int hash_value, int hash_value2){
  if(hash_table[hash_value].person == 0){
    hash_table[hash_value].person = hash_table_temp[1].person;
    hash_table[hash_value].deposition = hash_table_temp[1].deposition;
    hash_table[hash_value].surname = hash_table_temp[1].surname;
    hash_table[hash_value].forename = hash_table_temp[1].forename;
    hash_table[hash_value].age = hash_table_temp[1].age;
    hash_table[hash_value].type = hash_table_temp[1].type;
  }
  else if(hash_table[hash_value].person != 0){
    int k = 0;
    int i = 1;
    int double_hash;
    int hash_value2 = hash3(hash_table_temp[1].surname);
    while(k == 0){
      double_hash = (hash_value + i*hash_value2) % ARRAY_SIZE;
      if(hash_table[double_hash].person == 0){
        hash_table[double_hash].person = hash_table_temp[1].person;
        hash_table[double_hash].deposition = hash_table_temp[1].deposition;
        hash_table[double_hash].surname = hash_table_temp[1].surname;
        hash_table[double_hash].forename = hash_table_temp[1].forename;
        hash_table[double_hash].age = hash_table_temp[1].age;
        hash_table[double_hash].type = hash_table_temp[1].type;
        k = 1;
      }
      i++;
    }
  }
}
*/
void print_table(){
  for(int w = 0; w < ARRAY_SIZE; w++){
    if(hash_table[w].person != 0){
      printf("\n%d %s\n", hash_table[w].person, hash_table[w].surname);
    }
    else{
      //printf("\nEmpty\n");
    }
  }
}

void clear_temp(){
  hash_table[0].person = " ";
  hash_table[0].deposition = " ";
  hash_table[0].surname = " ";
  hash_table[0].forename = " ";
  hash_table[0].age = " ";
  hash_table[0].type = " ";
}
/*
int search(){

  for(int j = 0; j < ARRAY_SIZE; j++){
    if(hash_table_temp[1].surname == hash_table[j].surname){
      printf("\nthe if worked\n");
      return j;
    }
  }
  return -1;
}
*/
