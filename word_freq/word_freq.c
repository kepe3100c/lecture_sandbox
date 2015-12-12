#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fr,*fw;

int main()
{

  char noun[] = "名詞";  //名詞判定用
  char *pri;  //名詞判定用
  char *n_pri;  //
  char pp[400];
  char n_list_f[400];  //最終格納用
  char *num;  //名詞判定if時の本文に”名詞”という文字があった場合の判定回避用
  int i = 0,j = 0;  //loop counter

  //読み込みファイルオープン
  if((fr = fopen("kadai_25_r.txt","r")) == NULL){
    fprintf(stderr,"READ FILE ERROR !!");
    exit(0);
  }

  //書き込みファイルオープン
  if((fw = fopen("kadai_25_rr.txt","w")) == NULL){
    fprintf(stderr,"WRITE FILE ERROR !!");
    exit(0);
  }
  
  //1行ずつfgetsで読み込む
  //

  printf("ababa\n");
  
  while(fgets(pp,400,fr) != NULL){
    pri = strstr(pp,noun);
    if(pri != NULL){
      n_list_f[j] = pp[i];
      j++;
      i++;
    }else{
      i++;
    }
  }
  
  
  for(i = 0;i < 19;i++){
    printf("%s\n",n_list_f[i]);
  }
  
  
  
  return 0;
}
