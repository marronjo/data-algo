#include <stdio.h>

int main(){

  char name[20];
  int age;

  printf("Please enter your name: ");
  scanf("%s", name);
  printf("Please enter your age: ");
  scanf("%d", &age);

  printf("Name >> %s \n", name);
  printf("Age >> %d \n", age);
  printf("Hello %s (%d)", name, age);

  return 0;
}
