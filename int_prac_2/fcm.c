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
  // srand(time(NULL));

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
    // printf("%d,",muR[iCounter]);

  }

  /*体裁を整える改行出力（本質ではない）*/
  // printf("\n");

}

int main()
{
  char field[50];  // fgetsで1行格納用
  char xrange[400],yrange[400];  // 400行各特徴量格納用
  double center[4];  // クラスタの中心
  double centerM[4];  // クラスタの中心算出用、分母
  double mu[4][400];  // 各メンバシップのu
  double mu2[4][400];  // メンバシップコピー用
  double hant; // 判定用
  double hant2;  // 1くらいまであるかファジィ
  double hant3;
  double hant4[2];  // 
  double ipu = 5.0;
  int i,j,k = 0;
  int go = 0;
  
  // 乱数初期化
  // srand(time(NULL));
  
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
  
  // メンバシップ初期化1
  for(i = 0; i < 4; i++)
  {
    for(j = 0; j < 400; j++)
    {
      mu[i][j] = -1.0;
    }
  }
  
  rr();
  
  // メンバシップ初期化2
  for(i = 0; i < 400; i++)
  {
    for(j = 0; j < 4; j++)
    {
      if(j == 0)
      {
        mu[j][muR[i]] = ((rand() % 10) / 10.0);
        hant2 = 1 - mu[j][muR[i]];
      }else if(j != 3){
        hant3 = ((rand() % 10) / 10.0);
        if(signbit(hant2 - hant3) == 0)
        {
          mu[j][muR[i]] = hant3;
          hant2 = hant2 - hant3;
        }else{
          j--;
        }
      }else{
        mu[j][muR[i]] = hant2;
      }
    }
  }
  
  //
  for(i = 0; i < 400; i++)
  {
    // printf("Data[%d] : (%f)   (%f)   (%f)   (%f)\n", i, mu[0][i], mu[1][i], mu[2][i], mu[3][i]);
    // printf("Rand[%d] : %d\n",i,muR[i]);
  }
  
  // 
  int fuzz()
  {
    hant4[0] = 0.0;
    hant4[1] = 0.0;
    // 中心初期化
    for(i = 0; i < 4; i++)
    {
      center[i] = 0.0;
      centerM[i] = 0.0;
    }
    
    // 中心計算1
    for(i = 0; i < 4; i++)
    {
      for(j = 0; j < 400; j++)
      {
        center[i] += pow(mu[i][j],2.0) * sqrt(pow(xrange[j],2.0) + pow(yrange[j],2.0));
        centerM[i] += pow(mu[i][j],2.0);
      }
    }
    
    // 中心計算2
    for(i = 0; i < 4; i++)
    {
      center[i] = center[i] / centerM[i];
    }
    
    // メンバシップ更新、分母計算
    for(i = 0; i < 400; i++)
    {
      for(j = 0; j < 4; j++){
        mu2[j][i] = mu[j][i];
        hant4[0] += mu2[j][i];
        mu[j][i] += fabs(sqrt(pow(xrange[i],2.0) + pow(yrange[i],2.0)) - center[j]);
      }
    }
    
    // メンバシップ更新、全計算
    for(i = 0; i < 400; i++)
    {
      for(j = 0; j < 4; j++)
      {
        mu[j][i] = pow((fabs(sqrt(pow(xrange[i],2.0) + pow(yrange[i],2.0)) - center[j]) / mu[j][i]),2.0);
        hant4[1] += mu[j][i];
        //printf("%f\n",mu[j][i]);
      }
    }
    
    ipu = fabs(hant4[0] - hant4[1]);
    
    go++;
    
    return 0;
  }
  
  // εが十分に小さくなるまで繰り返し
  while(ipu > 0.0001)
  {
    fuzz();
    //printf("%d\n",k);
  }
  
  for(i = 0; i < 4; i++)
  {
    printf("Center[%d] = %f\n",i,center[i]);
  }
  
  
  for(i = 0; i < 400; i++)
  {
    // printf("Data[%d]\t: (%f)   (%f)   (%f)   (%f)\n", i, mu[0][i], mu[1][i], mu[2][i], mu[3][i]);
  }
  printf("ipu = %f\n%d\n",ipu,go);
  
}
