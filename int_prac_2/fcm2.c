#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAXRAND 400  /*乱数の最大値*/

FILE *fp;  // ファイルポインタ

int muR[400];  // 重複無しランダム値

int rr(void){

  int iaRandarray[MAXRAND]; /*乱数候補収納用変数*/
  int iCounter; /*ループカウンタ用変数*/
  int iNumRand; /*残り乱数候補数*/
  int iRandKey; /*乱数候補取得用変数*/
  int iRandVal; /*乱数の取得用変数*/

  /*乱数の種を初期化*/
  srand(time(NULL));

  /*あらかじめ配列に数値を代入しておく*/
  for( iCounter = 0 ; iCounter < MAXRAND ; ++iCounter){
    iaRandarray[ iCounter] = iCounter + 1;
  }

  /*テスト用ループ*/
  iNumRand = MAXRAND;
  for( iCounter = 0 ; iCounter < MAXRAND ; ++iCounter){

    /*乱数を取得*/
    iRandKey = rand() % iNumRand;

    /*配列の中身を乱数として取得する*/
    iRandVal = iaRandarray[ iRandKey ];

    /*つかった乱数を未使用の乱数で置き換える*/
    iaRandarray[ iRandKey ] = iaRandarray[ iNumRand - 1 ];

    /*乱数候補を一つ減らす*/
    --iNumRand;
    
    muR[iCounter] = iRandVal - 1;

    /*テスト用表示*/
    // printf("%d,",iRandVal);

  }

  /*体裁を整える改行出力（本質ではない）*/
  // printf("\n");

}

int main()
{
  char field[50];  // fgetsで1行格納用
  char xrange[400],yrange[400];  // 400行各特徴量格納用
  double center[4][2];  // クラスタの中心
  double centerM[4][2];  // クラスタの中心算出用、分母
  double mu[4][400];  // 各メンバシップのu
  double mu2[4][400];  // メンバシップコピー用
  double ipu = ;
  int i,j,k;
  
  // 乱数初期化
  srand(time(NULL));
  
  // 中心初期化
  for(i = 0; i < 4; i++){ center[i] = 0; }
  
  // fopenで開く
  if((fp = fopen("k.txt","r")) == NULL)
  {
    fprintf(stderr,"READ FILE ERROR !!");
    exit(0);
  }
  
  // fgets
  while((fgets(field,80,fp)) != NULL)
  {
    sscanf(field,"%lf %lf",&xrange[i], &yrange[i]);
    i++;
  }

  // メンバシップ初期化
  for(i = 0; i < 4; i++)
  {
    for(j = 0; j < 2; j++)
    {
      rr();
      for(k = 0; k < 400; k++)
      {
        if(k == 0)
        {
          mu[i][j][muR[k]] = 1 - ((rand() % 100) / 100);
        }else{
          if((muR[i][j][muR[k - 1]] - ((rand() % 100) / 100)) >= 0.00)
          {
            mu[i][j][muR[k]] = muR[i][j][muR[k - 1]] - ((rand() % 100) / 100);
          }else{
            muR[i][j][nuR[k]] = 0;
          }
        }
      }
    }
  }
  
  // a
  int fuzz()
  {
    // 中心初期化
    for(i = 0; i < 4; i++)
    {
      for(j = 0; j < 2; j++)
      {
        center[i][j] = 0;
        centerM[i][j] = 0;
      }
    }
    
    // 中心計算1
    for(i = 0; i < 4; i++)
    {
      for(j = 0; j < 2; j++)
      {
        for(k = 0; k < 400; k++)
        {
          if(j == 0){
            center[i][j] += mu[i][j][k] * mu[i][j][k] * xrange[k];
          }else{
            center[i][j] += mu[i][j][k] * mu[i][j][k] * yrange[k];
          }
          centerM[i][j] += mu[i][j][k] * mu[i][j][k];
        }
      }
    }
    
    // 中心計算2
    for(i = 0; i < 4; i++)
    {
      for(j = 0; j < 2; j++)
      {
        center[i][j] = center[i][j] / centerM[i][j];
      }
    }
    
    // メンバシップ初期化
    for(i = 0; i < 4; i++)
    {
      for(j = 0; j < 2; j++)
      {
        for(k = 0; k < 400; k++)
        {
          mu[i][j][k] = 0;
        }
      }
    }
    
    // メンバシップ更新、分母計算
    for(i = 0; i < 400; i++)
    {
      for(j = 0; j < 4; j++){
        mu2[j][0][i] = mu[j][0][i];
        mu2[j][1][i] = mu[j][1][i];
        mu[j][0][i] += sqrt(pow(xrange[i] - center[j][0],2.0));
        mu[j][1][i] += sqrt(pow(yrange[i] - center[j][1],2.0));
      }
    }
    
    // メンバシップ更新、全計算
    for(i = 0; i < 400; i++)
    {
      for(j = 0; j < 4; j++)
      {
        mu[j][0][i] = pow((mu2[j][0][i] - center[j][0]) / mu[j][0][i]),2.0);
        mu[j][1][i] = pow((mu2[j][1][i] - center[j][1]) / mu[j][1][i]),2.0);
      }
    }
  
  }
  
  // εが十分に小さくなるまで繰り返し
  while()
  {
    
  }
  
  
  return 0;
}
