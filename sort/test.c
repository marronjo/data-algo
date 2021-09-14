#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

bool check_repeats(int *array){
  for(int i = 0; i <= 10000; i++){
    for(int j = 0; j <= 10000; j++){
      if(array[i] == array[j] && i != j){
        return true; //there are repeats
      }
    }
  }
  return false; //no repeats
}

void generate_random(int *array){ //truly random numbers no repeats
  int r;
  srand((unsigned)time(NULL)); //seed based on time of day, which is always changing
  for(int i = 0; i <= 10000; i++){
    r = rand();
    array[i] = r;
    printf("%d  %d\n", i, r);
  }
}

void generate_random_repeats(int *array){ //array with definite repeats
  int r, m;
  for(int i = 0; i <= 10000; i++){
    r = rand();
    m = r % 7500; //10k values 7.5k % means definite repeats
    array[i] = m;
    printf("%d  %d\n", i, m);
  }
}

void generate_ascending(int *array){// array from 0 - 10,000
  for(int i = 0; i <= 10000; i++){
    array[i] = i;
  }
}

void generate_descending(int *array){ //array from 10,000 - 0,
  for(int i = 10000; i >= 0; i--){
    array[i] = i;
  }
}

void generate_uniform(int *array){ //array full of 7's
  for(int i = 0; i <= 10000; i++){
    array[i] = 7;
  }
}

int main(){
  generate_random_repeats();
}
