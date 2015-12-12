#include <stdio.h>
#include <math.h>

#define PI 3.141592

int main(void){

  float x1 = 329;               // x1
  float x2 = 827;               // x2
  float value = 2;              // value
  float totu1 = 0,totu2 = 0;    // for compute, mid
  float f1,f2,f3;               // goodness of fit
  int i,j,k;                    // counter
  
  for(i = 0; i < value; i++){
    totu1 += 0.5 * sin( (x1 * PI) / 1024 ) * cos( (20 * x1 * PI) / 1024 ) + 0.5;
  }
  
  for(i = 0; i < value; i++){
    totu2 += 0.5 * sin( (x2 * PI) / 1024 ) * cos( (20 * x2 * PI) / 1024 ) + 0.5;
  }

  f1 = (1 / value) * totu1;
  f2 = (1 / value) * totu2;
  
  printf("f1  = %.3f\nf2  = %.3f\n",f1,f2);
  printf("med = %.3f\n",(f1 + f2)/2);

  return 0;
}
