#include <stdio.h>
#include <math.h>

#define PI 3.141592

int fitnessCal(int cal)
{
    float precal1 = 0.0, precal2 = 0.0; // 途中計算用
    float value = 2; // nの値
    double chroms_f = 0,chroms_r = 0;	// 染色体、前半分、後ろ半分
    double base = 0;  // 10進数変換用
    double chroms[20]; // 染色体
    int i; // loop counter
    
    float f1,f2;

// printf("%d\n",cal);

    for (i = 0; i < 20; i++) { chroms[i] = 0; } // 初期化

    // 2進数変換
    for (i = 0; i < 20; i++)
    {
        chroms[i] = cal % 2;
        cal = cal / 2;
        printf("%.0f",chroms[i]);
    }
    printf("\n");
    
    for(i = 0; i < 20; i++)
    {
        if(i < 10)
        {
          chroms_r += pow(chroms[i] * 2,base);
          base++;
          if(i == 9){base = 0;} // べき乗リセット
        }else{
          chroms_f += pow(chroms[i] * 2,base);
          base++;
          //printf("%.0f\n",chroms_f);
        }
    }
    
printf("%.0f  %.0f\n",chroms_r,chroms_f);


    // 以下で適合度を計算
    for (i = 0; i < value; i++)
    {
        precal1 += 0.5 * sin((chroms_f * PI) / 1024) * cos((20 * chroms_f * PI) / 1024) + 0.5;
    }

    for (i = 0; i < value; i++)
    {
        precal2 += 0.5 * sin((chroms_r * PI) / 1024) * cos((20 * chroms_r * PI) / 1024) + 0.5;
    }

    f1 = (1 / value) * precal1;
    f2 = (1 / value) * precal2;
    
  // printf("f1  = %.3f\nf2  = %.3f\n",f1,f2);
  // printf("med = %.3f\n",(f1 + f2)/2);

    return 0;
}



int main(void){

  int x1 = 329;
  int x2 = 827;
  int x3 = 337723;
  double x4 = 337723;
  int bincom = 2;
  int totu = 0.0;
  int bin1[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  int i,remain;
  
  for(i = 0; i < 20; i++)
  {
    bin1[19 - i] = x3 % bincom;
    x3 = x3 / 2;
    // printf("%d\n",x3);
  }
  // printf("------------------\n");

  for(i = 0; i < 20; i++)
  {
    // printf("%d",bin1[i]);
  }
  // printf("\n01010010011100111011\n");

  fitnessCal(x4);
  
  return 0;
}
