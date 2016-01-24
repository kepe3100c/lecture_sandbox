#include <stdio.h>
#include <stdlib.h>

FILE *fp,*fp2;  // ファイルポインタ

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
  int lean_count = 0;  // 学習回数
  
  // 乱数初期化
  srand(time(NULL));
  
  // 重みをランダムに産出
  for(i = 0; i < 3; i++)
  {
    weight[i] = rand() % 20 - 10;
    weight[i] = weight[i] / 10;
    // printf("%f\n",weight[i]);
  }
  
  printf("Plot Line : %f + (%f * x) + (%f * y) = 0\n",(weight[0] / weight[2]), weight[1] / weight[2], weight[2] / weight[2]);
  
  // 初期化
  i = 0;
  
  // fopen
  if((fp = fopen("sample2v2.txt","r")) == NULL)
  {
     fprintf(stderr,"WRITE FILE ERROR !!");
     exit(0);
  }
  
  // fopen
  if((fp2 = fopen("niki.txt","w")) == NULL)
  {
     fprintf(stderr,"WRITE FILE ERROR !!");
     exit(0);
  }
  
  // fgets
  while((fgets(field,80,fp)) != NULL)
  {
    sscanf(field,"%lf %lf %lf",&xrange[i],&yrange[i],&clas[i]);
    // printf("xrange = %f : yrange = %f : class = %f\n",xrange[i],yrange[i],clas[i]);
    i++;
  }
  
  // printf("\nxrange = %f : yrange = %f : class = %f\n",xrange[0],yrange[0],clas[0]);
  
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
    fprintf(fp2,"%f\t%f\n",xrange[i],yrange[i]);
    // printf("xrange = %f : yrange = %f\n",xrange[i],yrange[i]);
  }
  
  fclose(fp2);
  
  // 
  // i = 1;
  
  // 学習巻数
  
  // 1ループあたり400回(単に400行あるから)
  while(i != 0)
  {
    i = 0;
    for(j = 0; j < 400; j++)
    {
      // 閾値初期化
      // act = 0;
  
      // 内積算出
      pr = (weight[0] * 1) + (weight[1] * xrange[j]) + (weight[2] * yrange[j]);
      // printf("%f\n",pr);
  
      // 閾値判定
      if(pr > 0)
      {
        act = 1;
      }else{
        act = 0;
      }
  
      // 学習するかどうか
      if(clas[j] != act)
      {
        // printf("Wrong ! : %f | %f\n",clas[j],act);
        pr =  clas[j] - act;
        // printf("Wrong act = %f : class = %f : δ = %f\n",act,clas[j],pr);
        weight[0] = (weight[0] + lean * 1 * pr);
        weight[1] = (weight[1] + lean * xrange[j] * pr);
        weight[2] = (weight[2] + lean * yrange[j] * pr);
      
        // printf("y = %f : x = %f : b = %f\n",weight[2],weight[1],weight[0]);
        i++;
      }
      
    }
    lean_count += i;
    // printf("Lean No = %d\n",i);
  }
  
  printf("Lean Count %d |  Plot Line : %f + (%f * x) + (%f * y) = 0\n",lean_count,(weight[0] / weight[2]), weight[1] / weight[2], weight[2] / weight[2]);
  
  // printf("i = %d : j = %d\n",i,j);
  
  for(i = 0; i < 6; i++)
  {
    // printf("Plot Line : %f + (%f * x) + (%f * y) = 0\n",(hout[i][0] / hout[i][2]) * 10, hout[i][1] / hout[i][2], hout[i][2] / hout[i][2]);
    // printf("Plot Line : %f * y = (%f * x) + %f\n",(-hout[i][2]) / (-hout[i][2]), (hout[i][1]) / (-hout[i][2]), (hout[i][0]) / (-hout[i][2]));
  }
  // printf("%d\n",k);
  
  return 0;
}
