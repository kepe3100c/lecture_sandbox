#include <stdio.h>
#include <stdlib.h>
#include <time.h>   // 乱数初期化用

#define SIZE 1048576  // 1024 * 1024

int randoms[10];

int mm()
{
  int i;

  // 乱数の種を初期化
	srand(time(NULL));

  for(i = 0; i < 10; i++)
  {
    randoms[i] = rand() % SIZE;
  }
  
  return 0;
}


int main()
{
  int i;

  mm();

  for(i = 0; i <10; i++)
  {
    printf("Randoms[%d] = %d\n",i,randoms[i]);
  }
  
}