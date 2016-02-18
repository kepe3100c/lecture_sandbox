#include <stdio.h>
#include <stdlib.h>

#define M 400
#define N 4

double xrange[400],yrange[400];  // x、y格納用
double fin[4][2];  // 最終的なメドイズ

int NUM[M];
int co = 0;

FILE *fp;  // ファイルポインタ

// メイズド求めるよ
void Med(int a,int b,int c,int d)
{
  double sum[4];  // 総和
  int medNam[4];  // 選択中メドイズナンバー
  int i,j,k,l;  // counter
  
  // 初期化
  for(i = 0; i < 4; i++){ sum[i] = 0;}
  
  // 調整、各メイズドナンバー格納
  medNam[0] = a - 1;
  medNam[1] = b - 1;
  medNam[2] = c - 1;
  medNam[3] = d - 1;
  
  // 総和算出
  for(i = 0; i < 4; i++)
  {
    for(j = 0; j < 400; j++)
    {
      sum[i] += (fabs(xrange[medNam[i]] - xrange[j]) + fabs(yrange[medNam[i]] - yrange[j]));
    }
    // printf("%f\n",sum[i]);
  }
  
  // printf("\n");
  
  // 1回目のみ直接ぶっこみ
  if(co == 0)
  {
    //printf("%d  %d  %d  %d\n",medNam[0],medNam[1],medNam[2],medNam[3]);
    for(i = 0; i < 4; i++)
    {
      fin[i][0] = medNam[i];
      fin[i][1] = sum[i];
      // printf("%.0f\t%.0f\n",fin[i][0],fin[i][1]);
    }
  }
  
  /*
  // 確認用
  if(co < 5)
  {
    for(i = 0; i < 4; i++)
    {
      printf("%0.f   \n",sum[i]);
    }
    printf("--\n");
  }
  */
  
  if(sum[0] < fin[0][1] && sum[1] < fin[1][1] && sum[2] < fin[2][1] && sum[3] < fin[3][1])
  {
    for(i = 0; i < 4; i++)
    {
      fin[i][0] = medNam[i];
      fin[i][1] = sum[i];
      // printf("%.0f\t%.0f\n",fin[i][0],fin[i][1]);
    }
  }
  
  
  co++;
}

void Perm(int n, int a)
{
  int i;
  static int c;
  if (n == N)
  {
    ++c;
    // printf("%4d : ", ++c);
    for (i = 0; i < N; i++)
    {
      // printf("%3d  ", NUM[i]);
    }
    // printf("\n");
    printf("%d  %d  %d  %d\n",NUM[0],NUM[1],NUM[2],NUM[3]);
    Med(NUM[0],NUM[1],NUM[2],NUM[3]);
    return;
  }

  for (i = a+1; i <= M; i++)
  {
    NUM[n] = i;
    Perm(n+1, i);
  }
}

int main()
{
  char field[50];  // fgetsで1行格納用
  int i = 0;
  
  // fopenで開く
  if((fp = fopen("k.txt","r")) == NULL)
  {
    fprintf(stderr,"READ FILE ERROR !!");
    exit(0);
  }
  
  // fgets
  while((fgets(field,80,fp)) != NULL)
  {
    sscanf(field,"%lf %lf",&xrange[i],&yrange[i]);
    i++;
  }
  
  Perm(0, 0);
  
  for(i = 0; i < 4; i++)
  {
    printf("%.0f  ",fin[i][0]);
  }
  printf("\n");
  
  return 0;
}
