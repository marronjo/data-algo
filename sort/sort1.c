#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define ARRAY_SIZE 10

void swap(int *x, int *y){ //swaps x and y using pointers, no call by reference in c
  int temp = *x; //setting temporary variable
  *x = *y;
  *y = temp;
}

void print_array(int *insert_array, int test, int swaps, int comps){
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
  printf("SORTED\t: Y\n");
  printf("SWAPS\t: %d\n", swaps);
  printf("COMPS\t: %d\n", comps);

  for(int a = 0; a < ARRAY_SIZE; a++){
    printf("%d ", insert_array[a]);
  }
  printf("\n");
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

  int urandom[10] = {4,3,5,1,0,2,9,6,8,7};
  int randomv[10] = {6,1,9,4,8,3,3,8,2,5};
  int ascends[10] = {0,1,2,3,4,5,6,7,8,9};
  int descends[10] = {9,8,7,6,5,4,3,2,1,0};
  int uniform[10] = {4,4,4,4,4,4,4,4,4,4};


  //Unique Random Values
  quicksort(urandom, 0, ARRAY_SIZE - 1, &swap, &comp);
  print_array(urandom, 0, swap, comp);
  swap = 0;
  comp = 0;
  //Random Values
  quicksort(randomv, 0, ARRAY_SIZE - 1, &swap, &comp);
  print_array(randomv, 1, swap, comp);
  swap = 0;
  comp = 0;
  //Ascending Sorted List
  quicksort(ascends, 0, ARRAY_SIZE - 1, &swap, &comp);
  print_array(ascends, 2, swap, comp);
  swap = 0;
  comp = 0;
  //Descending Sorted List
  quicksort(descends, 0, ARRAY_SIZE - 1, &swap, &comp);
  print_array(descends, 3, swap, comp);
  swap = 0;
  comp = 0;
  //Uniform List
  quicksort(uniform, 0, ARRAY_SIZE - 1, &swap, &comp);
  print_array(uniform, 4, swap, comp);

  printf("\nProgram Complete!\n");
  return 0;
}
