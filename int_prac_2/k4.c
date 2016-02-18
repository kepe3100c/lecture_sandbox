#include <stdio.h>
#include <stdlib.h>
#include <math.h>

FILE *fp;  // ファイルポインタ

int min(double a,double b,double c,double d)
{
  int mix = 9999;
  int go[4] = {a,b,c,d};
  int i,j = 0;
  
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
  char field[50];  // 一時格納用
  int med[4] = {223,240,247,248};  // 最適メドイズパターン
  double xrange[400],yrange[400];  // x、y格納用
  double hant[4];  // どれに一番近いか判定用
  int mimi;  // 最小値
  int clas[400]; // クラス格納用
  int i,j;  // counter
  
  // fopenで開く
  if((fp = fopen("k.txt","r")) == NULL)
  {
    fprintf(stderr,"READ FILE ERROR !!");
    exit(0);
  }
  
  // fgets
  while((fgets(field,80,fp)) != NULL)
  {
    sscanf(field,"%lf   %lf",&xrange[i],&yrange[i]);
    i++;
  }
  
  // fclose
  fclose(fp);
  
  for(i = 0; i < 400; i++)
  {
    // 各クラスのユークリッド距離算出
    for(j = 0; j < 4; j++)
    {
      // hant[j] = sqrt(pow(xrange[med[j]] - xrange[i],2) + pow(yrange[med[j]] - yrange[i],2));
      hant[j] = fabs(xrange[med[j]] - xrange[i]) + fabs(yrange[med[j]] - yrange[i]);
      printf("%f\n",hant[j]);
    }
    
    // 最小値算出
    mimi = min(hant[0],hant[1],hant[2],hant[3]);
    // printf("Min Clas = %d\n",mimi);

    // printf("Clas = %d\tMin Clas = %d\n",clas[i],mimi);
    
    // 各クラスに割り振り
    if(mimi == 0)
    {
      clas[i] = 0;
    }else if(mimi == 1){
      clas[i] = 1;
    }else if(mimi == 2){
      clas[i] = 2;
    }else{
      clas[i] = 3;
    }

  }
  
  // fopenで開く
  if((fp = fopen("k_f_2.txt","w")) == NULL)
  {
    fprintf(stderr,"READ FILE ERROR !!");
    exit(0);
  }
  
  // 書き出し
  for(i = 0; i < 400; i++)
  {
    fprintf(fp,"%f\t%f\t%d\n",xrange[i],yrange[i],clas[i]);
  }
  
  // fclose
  fclose(fp);
  
  return 0;
}
