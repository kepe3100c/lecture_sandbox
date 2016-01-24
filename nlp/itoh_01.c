#include <stdio.h>

FILE *in_file,*out_file;  // ファイルポインタ
  
int main()
{
  char field[81];  // fgetsで一時的に1行入れる用
  char *cmd = "cut -f3 nlp.txt | tr '\r\n' ' ' | tr ' ' '\n' | sort | grep -v '^\s*$' | uniq -c | sort -r";  // 実行コマンド
  
  // popenでコマンド実行結果をin_fileに
  if(!(in_file=popen(cmd,"r"))){
    printf(" cannot open out pipe!!");
    exit(0);
  }
 
  // fopenで書き込み用ファイルオープン
  if((out_file = fopen("nlp_f.txt","w")) == NULL){
    fprintf(stderr,"WRITE FILE ERROR !!");
    exit(0);
  }

  // fgetsでコマンド実行結果を書き込み用ファイルに
  while((fgets(field,80,in_file)) != NULL){
    fputs(field,out_file);
  }
  
  // close
  pclose(in_file);
  fclose(out_file);
  
  return 0;
}