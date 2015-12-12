#include <stdio.h>

int main(void){
  // char w1 = "ワード１";
  char *w2 = "ワード２";
  char wa1[10] = "abcdefg";
  // char *wa2[3] = "abx";
  // char wa3[2][2] = {"ab","cd"};
  int i;
  int po;
  
  po = strchr(wa1,"c");
  
  if(po != NULL)
  {
    wa1[po] = '\0';
  }
  
  printf("%s\n%s\n",w2,wa1);
  // printf("%s\n%s\n%s\n",w2,wa1,wa3[1][1]);
  
  return 0;
}
