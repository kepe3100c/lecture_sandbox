#include <stdio.h>
#include <stdlib.h>

FILE *in_file,*out_file;  // ファイルポインタ
  
int main()
{
  char *cmd = "cut -f3 nlp.txt | tr '\r\n' ' ' | tr ' ' '\n' | sort | grep -v '^\s*$' | uniq -c | sort -r | sed -e 's/^[ ]*//g' | sed -e 's/ /  /g'";  // 実行コマンド
  char field[81];  // fgetsで一時的に1行入れる用
  char eveProb[15];  // 発生確率、及び出力ファイルへの書き込み用
  double sum = 0;  // 頻度の総和
  double nowFreq;  // 処理中の行の頻度
  
  /* 実行コマンド        　：　説明
  
     cut -f3               ：　タブで句切られた文字を切り取り、オプションで3つ目を指定
     tr '\r\n' ' ' '\n'    ：  文字列の一括変換、winの改行を空白に変換
     tr ' ' '\n'           ：　文字列の一括変換、空白を改行に変換
     sort                  ：　行の整列、昇順にソート
     grep -v '^s\*$'       ：　文字列の検索、オプションで行末の空白を覗いて表示
     uniq -c               ：　重複の削除、オプションで重複回数を合わせて表示
     sort -r               ：　行の整列、降順にソート
     sed -e 's/^[]* //g'   ：　文字列の置換、行頭の空白を削除(コメントアウトが切れるため、*と/の間に半角空白を入れています)
     sed -e 's/ /  /g'     ：　文字列の変換、半角空白を2つに変換
     
  */
  
  // popenでコマンド実行結果をin_fileに入れる
  if(!(in_file=popen(cmd,"r")))
  {
    printf(" cannot open out pipe!!");
    exit(0);
  }
 
  // fopenで書き込み用ファイルオープン
  if((out_file = fopen("nlp_pri_f.txt","w")) == NULL)
  {
     fprintf(stderr,"WRITE FILE ERROR !!");
     exit(0);
  }
  
  // 頻度の総和を算出、fputsで一旦出力
  while((fgets(field,80,in_file)) != NULL)
  {
    sscanf(field,"%lf %s",&nowFreq,priPhoneme);
    sum += nowFreq;
    fputs(field,out_file);
  }
  
  // close
  pclose(in_file);
  fclose(out_file);

  // fopenで読み込み用ファイルオープン
  if((in_file = fopen("nlp_pri_f.txt","r")) == NULL)
  {
     fprintf(stderr,"READ FILE ERROR !!");
     exit(0);
  }

  // fopenで書き込み用ファイルオープン
  if((out_file = fopen("nlp_f.txt","w")) == NULL)
  {
     fprintf(stderr,"WRITE FILE ERROR !!");
     exit(0);
  }

  // 先ほど求めた頻度の総和で各頻度を割り、発生確率を算出
  // 発生確率を行頭に置いて出力
  while((fgets(field,80,in_file)) != NULL)
  {
    sscanf(field,"%lf %s",&nowFreq,priPhoneme);
    sprintf(eveProb,"%f  ",(nowFreq / sum));
    strcat(eveProb,field);
    fputs(eveProb,out_file);
  }
  
  // close
  fclose(in_file);
  fclose(out_file);
  
  return 0;
}
