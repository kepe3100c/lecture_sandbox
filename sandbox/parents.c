#include <stdio.h>

int main(void){
  int choise_parents[2];
  int chromoRN[10] = {0,0,1,0,1,1,0,0,0,0};
  int ichoise = 0;
  int i,j; // loop counter

  for(i = 0; i < 10; i++)
  {
    
    for(j = 0; j < 10; j++)
    {
      if(chromoRN[j] >= 9 -i)
      {
        if(ichoise > 1){i = 10; j = 10; printf("TWO CHOSED!!\n"); break;}
        
        choise_parents[ichoise] = j;
        if(ichoise > 0 && choise_parents[0] == choise_parents[1])
        {
          break;
        }else{
          ichoise++;
        }
      }
      
    }

  }
  
  printf("Chosed Parents\n1.chromosome%d\n2.chromosome%d\n",choise_parents[0],choise_parents[1]);

  printf("done\n");

  return 0;
}
