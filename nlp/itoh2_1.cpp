#include <iostream>
 
using namespace std;
 
int main(){
  char *cmd = "cut -f3 nlp.txt | tr '\r\n' ' ' | tr ' ' '\n' | sort | grep -v '^\s*$' | uniq -c | sort -r | sed -e 's/^[ ]*//g' | sed -e 's/ /  /g'";  // 実行コマンド
  char *cmd2 = "cut -f3 nlp.txt | tr '\r\n' '\n' | grep -v -e '^\s*$' | sed -e 's/ *$//g' | sed -e 's/^[ ]*/E /g' | sed -e 's/$/ B/g' | sort";  // バイグラム用
  char field[81];  // fgetsで一時的に1行入れる用
  char field2[81];  // fgetsで一時的に1行入れる用
  char eveProb[15];  // 発生確率、及び出力ファイルへの書き込み用
  char nowBy[30];  // バイグラムの1行格納用
  char sepBy[65000][5];  // バイグラム格納用
  char priPhoneme[10];  // 一時格納用
  double sum = 0;  // 頻度の総和
  double nowFreq;  // 処理中の行の頻度
  int lenBy;  // 読み込んだバイグラム1行の長さ格納用
  int i,j = 0, k = 0;  // カウンター、kはバイグラム格納時のフラグ用
  
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
  
  // popenでコマンド実行結果をin_file2に入れる
  if(!(in_file2=popen(cmd2,"r")))
  {
    printf(" cannot open out pipe!!");
    exit(0);
  }

  // fopenで書き込み用ファイルオープン
  if((out_file = fopen("nlp_f.txt","w")) == NULL)
  {
     fprintf(stderr,"WRITE FILE ERROR !!");
     exit(0);
  }
  
  while((fgets(field2,80,in_file2)) != NULL)
  {
    // sscanf(field2,"%s",nowBy);
    lenBy = strlen(field2);
    for(i = 0; i < lenBy; i++)
    {
      if(!isspace(field2[i]))
      {
        if(k == 1)
        {
          if(isspace(field2[i - 3]))
          {
            i = i - 2;
          }else if(field2[i - 4]){
            i = i - 3;
          }
          k = 0;
        }
        if(isprint(field2[i]))
        {
          fprintf(out_file,"%c",field2[i]);
        }
      }else{
        j++;
        if(j == 2)
        {
          fprintf(out_file,"%s","\n");
          j = 0;
          k = 1;
        }
      }
    }
  }

  // 先ほど求めた頻度の総和で各頻度を割り、発生確率を算出
  // 発生確率を行頭に置いて出力
  /*
  while((fgets(field,80,in_file)) != NULL)
  {
    sscanf(field,"%lf %s",&nowFreq,priPhoneme);
    sprintf(eveProb,"%f  ",(nowFreq / sum));
    strcat(eveProb,field);
    fputs(eveProb,out_file);
  }
  */
  
  // close
  fclose(in_file);
  fclose(in_file2);
  fclose(out_file);
  
  return 0;
}
