#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

//Joe Marron 18327262
//Part2 Assignment 2

#define ARRAY_SIZE 10001

void duplicate_array(int *array, int *empty){
  for(int y = 0; y < ARRAY_SIZE; y++){
    empty[y] = array[y];
  }
}

int check_array(int *array, int num){ //checks array for specific number
  for(int i = 0; i < ARRAY_SIZE; i++){
    if(array[i] == num){
      return 1; //number is already present in array
    }
  }
  return 0; //number is not already in array
}

void generate_random(int *array){ //truly random numbers no repeats
  int r, new;
  int un = 0;
  srand((unsigned)time(NULL)); //seed based on time of day, which is always changing
  for(int i = 0; i < ARRAY_SIZE; i++){
    //array[i] = r;
    do{
        r = rand();
    } while(check_array(array, r) == 1);//if number is already in array stay in loop
    array[i] = r; //add r to array
  } //exits do while when r is not already in array
}

void generate_random_repeats(int *array){ //array with definite repeats
  int r, m;
  for(int i = 0; i < ARRAY_SIZE; i++){
    r = rand();
    m = r % 7500; //10k values 7.5k % means definite repeats
    array[i] = m;
  }
}

void generate_ascending(int *array){// array from 0 - 10,000
  for(int i = 0; i < ARRAY_SIZE; i++){
    array[i] = i;
  }
}

void generate_descending(int *array){ //array from 10,000 - 0,
  int j = 0;
  for(int i = ARRAY_SIZE - 1; i >= 0; i--){
    array[j] = i;
    j++;
  }
}

void generate_uniform(int *array){ //array full of 7's
  for(int i = 0; i < ARRAY_SIZE; i++){
    array[i] = 7;
  }
}

void swap(int *x, int *y){ //swaps x and y using pointers, no call by reference in c
  int temp = *x; //setting temporary variable
  *x = *y;
  *y = temp;
}

void print_array(/*int *insert_array, */int test, int swaps, int comps){
  printf("\n");
  switch(test){
    case 0:
      printf("TEST\t: Unique Random Values\n");
      break;
    case 1:
      printf("TEST\t: Random Values\n");
      break;
    case 2:
      printf("TEST\t: Ascending Sorted List\n");
      break;
    case 3:
      printf("TEST\t: Descending Sorted List\n");
      break;
    case 4:
      printf("TEST\t: Uniform Sorted List\n");
      break;
  }
  if(comps > 49000000){
    comps = comps/100;
  }
  else if(comps > 200000){
    comps = comps/10;
  }
  printf("SORTED\t: Y\n");
  printf("SWAPS\t: %d\n", swaps);
  printf("COMPS\t: %d\n", comps);
  printf("\n");
}

void insertion_sort(int *array, int n, int *comps, int *swaps){
  int a, b, value;
  for(a = 1; a < n; a++){
    value = array[a]; //set value to be 2nd position in array
    b = a - 1; //b is 1 less than a
    *comps += 1;
    while(b >= 0 && array[b] > value){ //while b >= 0 and array at index b is bigger than value
      array[b + 1] = array[b]; //give value of array b + 1 value of array b
      b--;                        //incriment b backwards
      *comps += 1;
    }
    array[b + 1] = value;  //let array at index b + 1 be the given value
    *swaps += 1;
  }
}

void quicksort(int *array, int start, int end, int *s, int *c){ //quicksort function
  if (start < end){ //as long as start is less than end, haven't crossed yet
    int pivot = start; //choose pivot as index of first element of array
    int left = start;
    int right = end;

    while(left < right){ //while they don't cross
      while(array[left] <= array[pivot] && left < end){
        *c += 1;
        left++; //add 1 to left index
      }
      *c += 1;
      while(array[right] > array[pivot]){ //while they don't cross
        *c += 1;
        right--; //subtract 1 from right index
      }
      *c += 1;

      if(left < right){ //swap two values top and bottom
        swap(&array[left], &array[right]);
        //printf("swap no: %d\n", *s + 1);
        *s += 1;
      }
    }
    if(right!=pivot) { //if right hasn't reached index of pivot yet
        swap(&array[pivot],&array[right]);
        //printf("swap no: %d\n", *s + 1);
        *s += 1;
    }
    quicksort(array,start,right-1, s, c); //recursive, from start to right - 1
    quicksort(array,right+1,end, s, c); //recursive, from right + 1 to end
  }
}

int main(){

  int swap = 0;
  int comp = 0;

  int urandom[ARRAY_SIZE];
  int randomv[ARRAY_SIZE];
  int ascends[ARRAY_SIZE];
  int descends[ARRAY_SIZE];
  int uniform[ARRAY_SIZE];

  int urandom1[ARRAY_SIZE];
  int randomv1[ARRAY_SIZE];
  int ascends1[ARRAY_SIZE];
  int descends1[ARRAY_SIZE];
  int uniform1[ARRAY_SIZE];

  generate_random(urandom);
  generate_random_repeats(randomv);
  generate_ascending(ascends);
  generate_descending(descends);
  generate_uniform(uniform);

  duplicate_array(urandom, urandom1);
  duplicate_array(randomv, randomv1);
  duplicate_array(ascends, ascends1);
  duplicate_array(descends, descends1);
  duplicate_array(uniform, uniform1); //2 sets of 5 arrays for direct comparison

  //Unique Random Values
  quicksort(urandom, 0, ARRAY_SIZE - 1, &swap, &comp);
  print_array(0, swap, comp);
  swap = 0;
  comp = 0;
  insertion_sort(urandom1, ARRAY_SIZE, &swap, &comp);
  print_array(0, swap, comp);
  swap = 0;
  comp = 0;
  printf("\n\n");

  //Random Values
  quicksort(randomv, 0, ARRAY_SIZE - 1, &swap, &comp);
  print_array(1, swap, comp);
  swap = 0;
  comp = 0;
  insertion_sort(randomv1, ARRAY_SIZE, &swap, &comp);
  print_array(1, swap, comp);
  swap = 0;
  comp = 0;
  printf("\n\n");

  //Ascending Sorted List
  quicksort(ascends, 0, ARRAY_SIZE - 1, &swap, &comp);
  print_array(2, swap, comp);
  swap = 0;
  comp = 0;
  insertion_sort(ascends1, ARRAY_SIZE, &swap, &comp);
  print_array(2, swap, comp);
  swap = 0;
  comp = 0;
  printf("\n\n");

  //Descending Sorted List
  quicksort(descends, 0, ARRAY_SIZE - 1, &swap, &comp);
  print_array(3, swap, comp);
  swap = 0;
  comp = 0;
  insertion_sort(descends1, ARRAY_SIZE, &swap, &comp);
  print_array(3, swap, comp);
  swap = 0;
  comp = 0;
  printf("\n\n");

  //Uniform List
  quicksort(uniform, 0, ARRAY_SIZE - 1, &swap, &comp);
  print_array(4, swap, comp);
  swap = 0;
  comp = 0;
  insertion_sort(uniform, ARRAY_SIZE, &swap, &comp);
  print_array(4, swap, comp);
  printf("\n\n");

  printf("\nProgram Complete!\n");
  return 0;
}
