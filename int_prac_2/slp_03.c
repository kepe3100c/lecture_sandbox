#include <stdio.h>
#include<stdlib.h>

FILE *fp;  // ファイルポインタ

int main(void){
  
  char field[81];  // fgetsで一時的に1行入れる用
  double xrange[400],yrange[400],clas[400];  // xとyとclass格納用
  double xymin[2],xymax[2];  // xとyのminとmax格納用
  double weight[3];  // 重み
  double lean = 0.01;  // 学習率
  double pr;  // 重み・データの内積及びδ用
  double act = 0;  // 閾値
  double hout[6][3];  // プロット用
  int i,j,k = 0;
  
  // 乱数初期化
  srand(time(NULL));
  
  // 重みをランダムに産出
  for(i = 0; i < 3; i++)
  {
    weight[i] = rand() % 20 - 10;
    weight[i] = weight[i] / 10;
    // printf("%f\n",weight[i]);
  }
  
  // 初期化
  i = 0;
  
  // fopen
  if((fp = fopen("sample2.dat","r")) == NULL)
  {
     fprintf(stderr,"WRITE FILE ERROR !!");
     exit(0);
  }
  
  // fgets
  while((fgets(field,80,fp)) != NULL)
  {
    sscanf(field,"%lf   %lf   %lf",&xrange[i],&yrange[i],&clas[i]);
    // printf("xrange = %f : yrange = %f : class = %f\n",xrange[i],yrange[i],clas[i]);
    i++;
  }
  
  // printf("\nxrange = %f : yrange = %f : class = %f\n",xrange[0],yrange[0],clas[0]);
  
  /*
  // max,min算出
  for(i = 0; i < 400; i++)
  {
    if(i == 0)
    {
      xymin[0] = xrange[0];
      xymin[1] = yrange[0];
      xymax[0] = xrange[0];
      xymax[1] = yrange[0];
      // printf("xMax = %f : yMax = %f : xMin = %f : yMin = %f\n",xymax[0],xymax[1],xymin[0],xymin[1]);
    }else{
      if(xrange[i] > xymax[0])
      {
        xymax[0] = xrange[i];
      }
      
      if(yrange[i] > xymax[1])
      {
        xymax[1] = yrange[i];
      }
      
      if(xrange[i] < xymin[0])
      {
        xymin[0] = xrange[i];
      }
      
      if(yrange[i] < xymin[1])
      {
        xymin[1] = yrange[i];
      }
      
    }
  }
  
  // printf("xMax = %f : yMax = %f : xMin = %f : yMin = %f\n",xymax[0],xymax[1],xymin[0],xymin[1]);
  
  // 0~1に変換
  for(i = 0; i < 400; i++)
  {
    xrange[i] = (xrange[i] - xymin[0]) / (xymax[0] - xymin[0]);
    yrange[i] = (yrange[i] - xymin[1]) / (xymax[1] - xymin[1]);
    // printf("xrange = %f : yrange = %f\n",xrange[i],yrange[i]);
  }
  
  // 初期化
  i = 0;
  */
  // 学習回数
  
  // 1ループあたり400回(単に400行あるから)
  for(j = 0; j < 400; j++)
  {
    // 閾値初期化
    act = 0;
  
    // 内積算出
    pr = (weight[0] * 1) + (weight[1] * xrange[j]) + (weight[2] * yrange[j]);
    // printf("%f\n",pr);
  
    // 閾値判定
    if(pr > 0)
    {
      act = 1;
    }
  
    // 学習するかどうか
    if(clas[j] != act)
    {
      // printf("Wrong ! : %d | %f\n",j,pr);
      pr =  clas[j] - act;
      // printf("Wrong act = %f : class = %f : δ = %f\n",act,clas[j],pr);
      weight[0] = (weight[0] + lean * 1 * pr);
      weight[1] = (weight[1] + lean * xrange[j] * pr);
      weight[2] = (weight[2] + lean * yrange[j] * pr);
      
      // printf("y = %f : x = %f : b = %f\n",weight[2],weight[1],weight[0]);
      
      j = -1;
      i++;
    }
        
    // プロット用方程式の各値を格納
    // if(j % 20 == 0 || j == 99)
    // {
    //  hout[k][0] = weight[0];
    //  hout[k][1] = weight[1];
    //  hout[k][2] = weight[2];
    //  printf("%d  :  %f  :  %f  :  %f\n", i, hout[k][0], hout[k][1], hout[k][2]);
    //  k++;
    // }
    
  }
  
  printf("Lean %d   |   Plot Line : %f + (%f * x) + (%f * y) = 0\n",i,(weight[0] / weight[2]), weight[1] / weight[2], weight[2] / weight[2]);
  
  // 2ループ、800回
  // for(k = 0; k < 2; k++)
  // {
    // loop();
  // }
  
  // printf("i = %d : j = %d\n",i,j);
  
  for(i = 0; i < 6; i++)
  {
    // printf("Plot Line : %f + (%f * x) + (%f * y) = 0\n",(hout[i][0] / hout[i][2]) * 10, hout[i][1] / hout[i][2], hout[i][2] / hout[i][2]);
    // printf("Plot Line : %f * y = (%f * x) + %f\n",(-hout[i][2]) / (-hout[i][2]), (hout[i][1]) / (-hout[i][2]), (hout[i][0]) / (-hout[i][2]));
  }
  // printf("%d\n",k);
  
  return 0;
}
