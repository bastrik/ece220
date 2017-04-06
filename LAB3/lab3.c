#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
  int arr1[5] = {1,2,3,4,5};

  int arr2[5];

  printf("int size: %lu, pointer size: %lu\n", sizeof(int), sizeof(int *));
  int i;
  for (i = 0; i < 5; i++)
  {
  	arr2[i] = &arr1[i];
  }

  for (i = 0; i < 5; i++)
  {
  	printf("%p, answer:%p\n", arr2[i], (arr1+i));
  }

  return 0;
}

