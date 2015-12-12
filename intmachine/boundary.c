#include <stdio.h>
#include <stdlib.h>

// ファイルポインタ
FILE *fr;

int main()
{
  double corrMatrix[250][2];   // 行列Z
  double corrMatrix_sample[2][10] = {{6.4,11.4,2.4,1.6,16.6,6.6,5.6,4.4,1.6,7.4},{2.3,8.3,4.3,1.7,10.7,8.7,4.7,5.3,1.7,1.3}};  // プリントの行列Z
  double corrMatrix_c[3] = {0,0,0}; // covariance matrix
  double corrMatrix_c_sample[3] = {0,0,0}; // covariance matrix
  double corrAverage[2] = {0,0}; // 平均
  char pri1[10],pri2[10]; // 一時格納用
  int i;  // loop counter
  
  // ファイルオープン
  if((fr = fopen("DataMatrixCovar6PSau.dat","r")) == NULL)
  {
    fprintf(stderr,"READ FILE OPEN ERROR !!");
    // exit(0);
  }

  // fscanfで読み込み
  for(i = 0; i < 250; i++)
  {
    fscanf(fr,"%s %s",&pri1,&pri2);
    corrMatrix[i][0] = atof(pri1);
    corrMatrix[i][1] = atof(pri2);
    corrAverage[0] += corrMatrix[i][0];
    corrAverage[1] += corrMatrix[i][1];
    // printf("%f %f\n",corrMatrix[i][0],corrMatrix[i][1]);
  }
  
  corrAverage[0] = corrAverage[0] / 250;
  corrAverage[1] = corrAverage[1] / 250;
  printf("average1 : %f\naverage2 : %f\n",corrAverage[0],corrAverage[1]);
  
  for(i = 0; i < 250; i++)
  {
    corrMatrix[i][0] = corrMatrix[i][0] - corrAverage[0];
    corrMatrix[i][1] = corrMatrix[i][1] - corrAverage[1];
    printf("%.1f %.1f\n\n",corrMatrix[i][0],corrMatrix[i][1]);
  }
  
  // 処理
  for(i = 0; i < 250; i++)
  {
    corrMatrix_c[0] += corrMatrix[i][0] * corrMatrix[i][0];
    corrMatrix_c[1] += corrMatrix[i][0] * corrMatrix[i][1];
    corrMatrix_c[2] += corrMatrix[i][1] * corrMatrix[i][1];
    // printf("0.0 = %.1f   0.1 = %.1f   1.1 = %.1f\n",corrMatrix_c[0],corrMatrix_c[1],corrMatrix_c[2]);
  }
  
  // データ数-1で割る
  for(i = 0; i < 3; i++)
  {
    corrMatrix_c[i] = corrMatrix_c[i] / 249;
  }
  
  // fclose
  fclose(fr);
  
  // 確認
  printf("covariance matrix\n[ %.1f  %.1f ]\n[ %.1f  %.1f ]\n",corrMatrix_c[0],corrMatrix_c[1],corrMatrix_c[1],corrMatrix_c[2]);

  
  for(i = 0; i < 10; i++)
  {
    corrMatrix_c_sample[0] += corrMatrix_sample[0][i] * corrMatrix_sample[0][i];
    corrMatrix_c_sample[1] += corrMatrix_sample[0][i] * corrMatrix_sample[1][i];
    corrMatrix_c_sample[2] += corrMatrix_sample[1][i] * corrMatrix_sample[1][i];
  }
  
  corrMatrix_c_sample[0] = corrMatrix_c_sample[0] / 9;
  corrMatrix_c_sample[1] = corrMatrix_c_sample[1] / 9;
  corrMatrix_c_sample[2] = corrMatrix_c_sample[2] / 9;

  // 確認
  printf("covariance matrix sample\n[ %.1f  %.1f ]\n[ %.1f  %.1f ]\n",corrMatrix_c_sample[0],corrMatrix_c_sample[1],corrMatrix_c_sample[1],corrMatrix_c_sample[2]);

}
