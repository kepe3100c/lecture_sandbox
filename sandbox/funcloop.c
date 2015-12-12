#include <stdio.h>

int main(void){
  int i;

  int looper(int oi)
  {
    printf("%d\n",oi);
  }
  
  for(i = 0; i < 10; i++)
  {
    looper(i);
  }
  
  return 0;
}
