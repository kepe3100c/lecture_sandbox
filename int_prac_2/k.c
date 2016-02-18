#include <stdio.h>
#include <stdlib.h>
#include <math.h>

FILE *fp,*fp2;  // ファイルポインタ

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

int main(void){
  
  char field[50];  // fgetsで1行格納用
  double xrange[400],yrange[400];  // x、y格納用
  double kSum[4][3];  // 各クラスタ総和
  double hant[4];  // どれに一番近いか判定用
  int clas[400]; // クラス格納用
  int mimi;  // 最小値
  int wrong = 1;  // 間違い回数
  int i = 0,j;  // counter
  
  // 乱数初期化
  srand(time(NULL));
  
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
  
  // クラス適当割り振り
  for(i = 0; i < 400; i++)
  {
    clas[i] = rand() % 4;
    // printf("%d : %d\n",i,clas[i]);
  }
  
  int loop()
  {
    // 初期化
    wrong = 0;
    
    // 初期化
    for(i = 0; i < 4; i++)
    {
      for(j = 0; j < 3; j++)
      {
        kSum[i][j] = 0;
      }
      hant[i] = 0;
    }
    
    // 各xとyの総和、データ数を算出
    for(i = 0; i < 400; i++)
    {
      if(clas[i] == 0)
      {
        kSum[0][0] += xrange[i];
        kSum[0][1] += yrange[i];
        kSum[0][2]++;
      }else if(clas[i] == 1){
        kSum[1][0] += xrange[i];
        kSum[1][1] += yrange[i];
        kSum[1][2]++;
      }else if(clas[i] == 2){
        kSum[2][0] += xrange[i];
        kSum[2][1] += yrange[i];
        kSum[2][2]++;
      }else{
        kSum[3][0] += xrange[i];
        kSum[3][1] += yrange[i];
        kSum[3][2]++;
      }
    }
    
    // 総和をデータ数で割るよ
    for(i = 0; i < 4; i++)
    {
      kSum[i][0] = kSum[i][0] / kSum[i][2];
      kSum[i][1] = kSum[i][1] / kSum[i][2];
    }
    
    // 
    for(i = 0; i < 400; i++)
    {
      // 各クラスのユークリッド距離算出
      for(j = 0; j < 4; j++)
      {
        hant[j] = sqrt(pow(kSum[j][0] - xrange[i],2) + pow(kSum[j][1] - yrange[i],2));
        // printf("%f\n",hant[j]);
      }
      
      // 最小値算出
      mimi = min(hant[0],hant[1],hant[2],hant[3]);
      // printf("Min Clas = %d\n",mimi);
    
      // 最小値のクラスに設定
      if(clas[i] != mimi)
      {
        // printf("Clas = %d\tMin Clas = %d\n",clas[i],mimi);
        
        // 間違い回数インクリメント
        wrong++;
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
        // printf("Wrong\n");
      }
    }
  
  }
  
  while(wrong != 0)
  {
    // printf("Wrong = %d\n",wrong);
    // wrong = 0;
    loop();
  }
  
  // fopenで開く
  if((fp2 = fopen("k_f_1.txt","w")) == NULL)
  {
    fprintf(stderr,"READ FILE ERROR !!");
    // exit(0);
  }
  
  for(i = 0; i < 400 ; i++)
  {
    fprintf(fp2,"%f\t%f\t%d\n",xrange[i],yrange[i],clas[i]);
  }
  
  // fclose
  fclose(fp2);
  
  return 0;
}
