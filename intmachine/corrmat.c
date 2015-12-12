#include <stdio.h>
#include <stdlib.h>

// ファイルポインタ
FILE *fr;

int main()
{
  double corrMatrix[500][2];   // 行列Z
  double corrMatrix_c[3] = {0,0,0}; // covariance matrix
  double corrAverage[2] = {0,0}; // 平均
  char pri1[10],pri2[10]; // 一時格納用
  char fn[30]; // ファイル名格納用
  int flength; // ファイルのデータの長さ
  int i;  // loop counter
  
  // ファイル名
  printf("File Name ? : ");
  scanf("%s",fn);
  
  // データの長さ
  printf("Input Data Length ? : ");
  scanf("%d",&flength);
  
  // ファイルオープン
  if((fr = fopen(fn,"r")) == NULL)
  {
    fprintf(stderr,"READ FILE OPEN ERROR !!");
    // exit(0);
  }

  // fscanfで読み込み、Zを生成
  for(i = 0; i < flength; i++)
  {
    fscanf(fr,"%s %s",&pri1,&pri2);
    corrMatrix[i][0] = atof(pri1);
    corrMatrix[i][1] = atof(pri2);
    corrAverage[0] += corrMatrix[i][0];
    corrAverage[1] += corrMatrix[i][1];
    // printf("%f %f\n",corrMatrix[i][0],corrMatrix[i][1]);
  }
  
  corrAverage[0] = corrAverage[0] / flength;
  corrAverage[1] = corrAverage[1] / flength;
  printf("average1 : %f\naverage2 : %f\n",corrAverage[0],corrAverage[1]);
  
  for(i = 0; i < flength; i++)
  {
    corrMatrix[i][0] = corrMatrix[i][0] - corrAverage[0];
    corrMatrix[i][1] = corrMatrix[i][1] - corrAverage[1];
    // printf("%.1f %.1f\n\n",corrMatrix[i][0],corrMatrix[i][1]);
  }
  
  // 処理
  for(i = 0; i < flength; i++)
  {
    corrMatrix_c[0] += corrMatrix[i][0] * corrMatrix[i][0];
    corrMatrix_c[1] += corrMatrix[i][0] * corrMatrix[i][1];
    corrMatrix_c[2] += corrMatrix[i][1] * corrMatrix[i][1];
    // printf("0.0 = %.1f   0.1 = %.1f   1.1 = %.1f\n",corrMatrix_c[0],corrMatrix_c[1],corrMatrix_c[2]);
  }
  
  // データ数-1で割る
  for(i = 0; i < 3; i++)
  {
    corrMatrix_c[i] = corrMatrix_c[i] / (flength - 1);
  }
  
  // fclose
  fclose(fr);
  
  // 確認
  printf("covariance matrix\n[ %.1f  %.1f ]\n[ %.1f  %.1f ]\n",corrMatrix_c[0],corrMatrix_c[1],corrMatrix_c[1],corrMatrix_c[2]);

}
