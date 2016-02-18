#include <stdio.h>

#define M 9
#define N 5

int NUM[M];

int min(int a,int b,int c,int d)
{
  int mix = 9999;
  int go[4] = {a,b,c,d};
  int i,j;
  
  for(i = 0; i < 4; i++){
    if(go[i] < mix){
      mix = go[i];
      j = i;
    }
  }
  
  return j;
}

int main()
{
    int i;
    
    i = min(5,6,0,0);
    
    printf("Min = %d\n",i);

    return 0;
}