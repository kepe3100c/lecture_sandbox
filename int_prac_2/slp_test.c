#include <stdio.h>
#include<stdlib.h>

FILE *fp;  // ファイルポインタ

int main(void){
  
  char field[81];  // fgetsで一時的に1行入れる用
  double xrange[400],yrange[400],clas[400];  // xとyとclass格納用
  double xymin[2],xymax[2];  // xとyのminとmax格納用
  double weight[3];  // 重み
  int i,j;
  
  // 乱数初期化
  srand(time(NULL));
  
  // 重み
  for(i = 0; i < 3; i++)
  {
    weight[i] = rand() % 20 - 10;
    weight[i] = weight[i] / 10;
    printf("%f\n",weight[i]);
  }
  
  
  return 0;
}