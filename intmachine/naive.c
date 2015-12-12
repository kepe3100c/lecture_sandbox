#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// ファイルポインタ
FILE *fr;

int main()
{
  double dave[1000][3];  // 前3つの格納用
  double ave[2][3];  // 平均格納用、1.熱、2.血圧、3.脈拍
  double disp[2][3];  // 分散格納用、上に同じ
  double inputv[3] = {38.5,75.0,50.0};  // 判別したいデータ格納用、上に同じ
  double condp[2][4];  // 条件付き確率格納用
  double decision = 1.5;  // インフルエンザと頭痛の関係判定用
  double pp[2] = {0,0};  // 事前確率格納用、1.No、2.Yes
  double corrp = 0;  // 頭痛とインフルの相関があるかどうかの判定用
  double flength;  // データ数
  char fn[30]; // ファイル名格納用
  char pri1[10],pri2[10],pri3[10],pri4[10],pri5[10];  // 一時格納用
  char inputw[] = "No";  // 判別したいデータ格納用、頭痛の有無
  int i,j;  // loop counter
  
  // 初期化
  for(i = 0; i < 2; i++){ for(j = 0; j < 4; j++){ condp[i][j] = 0; } }
  for(i = 0; i < 2; i++){ for(j = 0; j < 3; j++){ ave[i][j] = 0; disp[i][j] = 0; } }
  
  // ファイル名
  // printf("File Name ? : ");
  // scanf("%s",fn);
  
  // データの長さ
  printf("Input Data Length ? : ");
  scanf("%lf",&flength);

  // 判別したいデータ
  // printf("How the data what you want to distinguish ?\n");
  // printf("Temp BloodPleasure BloodBeat Headache(Yes/No) : ");
  // scanf("%lf %lf %lf %s",&inputv[0],&inputv[1],&inputv[2],inputw);

  
  // ファイルオープン
  if((fr = fopen("nave.txt","r")) == NULL)
  {
    fprintf(stderr,"READ FILE OPEN ERROR !!");
    // exit(0);
  }
  // fscanfでファイルから各データを読み込み
  for(i = 0; i < flength; i++)
  {
    fscanf(fr,"%s %s %s %s %s",&pri1,&pri2,&pri3,pri4,pri5);

    // 文字から変換して格納
    dave[i][0] = atof(pri1);
    dave[i][1] = atof(pri2);
    dave[i][2] = atof(pri3);
    
    // printf("%f  %f  %f  %s  %s\n",dave[i][0],dave[i][1],dave[i][2],pri4,pri5);

    // 頭痛とインフルエンザの関係確認用
    if(strlen(pri4) == strlen(pri5))
    {
      corrp++;
    }
    
    // 事前確率用
    if(strlen(pri5) < 3)
    {
      // No
      pp[0]++;
    }else{
      // Yes
      pp[1]++;
    }
  }

  // fclose
  fclose(fr);
  
  // 頭痛とインフルエンザが関係について判別
  if(decision > (flength / corrp))
  {
    printf("%f\n",flength / corrp);
    corrp = 1.0;
  }
  
  // 事前確率算出
  // pp[0] = pp[0] / flength;
  // pp[1] = pp[1] / flength;
  // printf("PP = %f : %f\n",pp[0],pp[1]);
  
  // 平均算出用にすべて足し込む
  for(i = 0; i < flength; i++)
  {
    if(i <= 400)
    {
      ave[0][0] += dave[i][0];
      ave[0][1] += dave[i][1];
      ave[0][2] += dave[i][2];
    }else{
      ave[1][0] += dave[i][0];
      ave[1][1] += dave[i][1];
      ave[1][2] += dave[i][2];
    }
      
  }
  
  // 平均を算出
  for(i = 0; i < 3; i++)
  {
    ave[0][i] = ave[0][i] / (flength / 2.0);
    ave[1][i] = ave[1][i] / (flength / 2.0);
    printf("Average = %f : %f\n",ave[0][i],ave[1][i]);
  }
  
  // 分散算出用にすべて足し込む
  for(i = 0; i < flength; i++)
  {
    if(i < 400)
    {
      disp[0][0] += pow((dave[i][0] - ave[0][0]),2.0);
      disp[0][1] += pow((dave[i][1] - ave[0][1]),2.0);
      disp[0][2] += pow((dave[i][2] - ave[0][2]),2.0);
    }else{
      disp[1][0] += pow((dave[i][0] - ave[1][0]),2.0);
      disp[1][1] += pow((dave[i][1] - ave[1][1]),2.0);
      disp[1][2] += pow((dave[i][2] - ave[1][2]),2.0);
    }
  }
  
  // 分散を算出
  for(i = 0; i < 3; i++)
  {
    disp[0][i] = disp[0][i] / (flength / 2.0);
    disp[1][i] = disp[1][i] / (flength / 2.0);
    printf("Disp = %f : %f\n",disp[0][i],disp[1][i]);
  }
  
  // 条件付き確率を算出
  for(i = 0; i < 3; i++)
  {
    condp[0][i] = (1.0 / (sqrt(2.0 * M_PI) * sqrt(disp[0][i]))) * exp(-0.5 * (pow(inputv[i] - ave[0][i],2.0) / disp[0][i]));
    condp[1][i] = (1.0 / (sqrt(2.0 * M_PI) * sqrt(disp[1][i]))) * exp(-0.5 * (pow(inputv[i] - ave[1][i],2.0) / disp[1][i]));
  }
  
  // 条件付確率参照
  printf("Condp1 = %f  %f  %f\n",condp[0][0],condp[0][1],condp[0][2]);
  printf("Condp2 = %f  %f  %f\n",condp[1][0],condp[1][1],condp[1][2]);
  
  // 再利用しつつ算出、格納
  condp[0][0] = condp[0][0] * condp[0][1] * condp[0][2];
  condp[1][0] = condp[1][0] * condp[1][1] * condp[1][2];
  
  printf("Condp = %f : %f\n",condp[0][0],condp[1][0]);
  
  // 頭痛とインフルの関係があるならばフィルターをかける
  if(corrp == 1)
  {
    // 判別したいデータの頭痛の有無からフィルターをかける先を決定、実行
    // 確率的に半分になるようなフィルター
    if(strlen(inputw) > 2)
    {
      condp[0][0] = condp[0][0] * 0.5;
    }else{
      condp[1][0] = condp[1][0] * 0.5;
    }
  }
  
  // クラス判別及び結果出力
  if(condp[0][0] > condp[1][0])
  {
    printf("\nClass1(don't) : %f\nClass2(have) : %f\nInput your data distinguished to Class1(don't)\n",condp[0][0],condp[1][0]);
  }else{
    printf("\nClass1(don't) : %f\nClass2(have) : %f\nInput your data distinguished to Class2(have)\n",condp[0][0],condp[1][0]);
  }
  
}
