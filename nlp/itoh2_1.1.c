#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *in_file,*in_file2,*out_file;  // ファイルポインタ
  
int main()
{
  char *cmd = "cut -f3 nlp.txt | tr '\r\n' ' ' | tr ' ' '\n' | sort | grep -v '^\s*$' | uniq -c | sort -r | sed -e 's/^[ ]*//g' | sed -e 's/ /  /g' > nlp_pri_01.txt";  // 実行コマンド
  char *cmd2 = "cut -f3 nlp.txt | tr '\r\n' '\n' | grep -v -e '^\s*$' | sed -e 's/ *$//g' | sed -e 's/^[ ]*/E /g' | sed -e 's/$/ B/g' | sort";  // バイグラム用
  char *cmd3 = "sort nlp_f.txt | uniq -c | sed -e 's/^[ ]*//g' > nlp_pri_f2.txt";
  char field[81],field2[81];  // fgetsで一時的に1行入れる用
  char priPhoneme[10],priPhoneme2[10];  // 音素一時格納用、ユニグラム用とバイグラム用
  double sumUni = 0;  // 音素数
  double nowFreq,nowFreq2;  // 処理中の行の頻度、ユニグラム用とバイグラム用
  int lenBy;  // 読み込んだバイグラム1行の長さ格納用
  int i,j = 0;  // カウンター
  int k = 0; // バイグラム格納時のフラグ用
  
  /* 実行コマンド        　：　説明 (重複してるものは省略)
     
     ->cmd
     
     cut -f3               ：　タブで句切られた文字を切り取り、オプションで3つ目を指定
     tr '\r\n' ' ' '\n'    ：  文字列の一括変換、winの改行を空白に変換
     tr ' ' '\n'           ：　文字列の一括変換、空白を改行に変換
     sort                  ：　行の整列、昇順にソート
     grep -v '^s\*$'       ：　文字列の検索、オプションで行末の空白を覗いて表示
     uniq -c               ：　重複の削除、オプションで重複回数を合わせて表示
     sort -r               ：　行の整列、降順にソート
     sed -e 's/^[]* //g'   ：　文字列の置換、行頭の空白を削除(コメントアウトが切れるため、*と/の間に半角空白を入れています)
     sed -e 's/ /  /g'     ：　文字列の変換、半角空白を2つに変換
     
     ->cmd2
     
     cut -f3               ：　省略
     tr '\r\n' '\n'        ：　文字列の一括変換、winの改行をunixの改行に変換
     grep -v -e '^\s*$'    ：　省略
     sed -e 's/ *$//g'     ：　文字列の置換、行末の空白を削除
     sed -e 's/^[ ]* /E /g'：　文字列の置換、行頭に"E "を挿入、これは行頭ということで挿入(コメントアウトが切れるため、*と/の間に半角空白を入れています)
     sed -e 's/$/ B/g'     ：　文字列の置換、行末に"B "を挿入、これは行末ということで挿入
     sort                  ：　省略
     
     ->cmd3
     
     sort                  ：　省略
     uniq -c               ：　省略
     sed -e 's/^[ ]* //g'　：　省略
     
  */
  
  // popenでコマンド実行結果をin_fileに入れる
  if(!(in_file = popen(cmd,"r")))
  {
    printf(" cannot open out pipe!!");
    exit(0);
  }
 
  // fopenで書き込み用ファイルオープン
  if((out_file = fopen("nlp_pri_01.txt","w")) == NULL)
  {
     fprintf(stderr,"WRITE FILE ERROR !!");
     exit(0);
  }
  
  // fputsで一旦出力
  while((fgets(field,80,in_file)) != NULL)
  {
    fputs(field,out_file);
  }
  
  // close
  pclose(in_file);
  fclose(out_file);
  
  // コマンド実行、
  system(cmd);

  // fopenで読み込み用ファイルオープン
  if((in_file = fopen("nlp_pri_01.txt","r")) == NULL)
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

  // バイグラム格納
  // fgetsで取り出した文字列に対して、1文字ずつ、スペースかどうかを基本に判定していく
  // スペースでは無い場合にファイルに1文字書き込む、また、isprintで印字可能かを判定し、改行コードを避ける
  // スペースの回数をカウントして、2回スペースがあったらフラグを立てて1回改行の処理
  // 改行のフラグから、カウンタを適切な値に調整し、再度ループを回す
  // カウンタの適切な値はif(k == 1)内に記述、基本的には現在探索中の文字列中で、
  // 何個前がスペースだったかを見て、それぞれに該当する処理を行う
  while((fgets(field2,80,in_file2)) != NULL)
  {
    lenBy = strlen(field2);
    for(i = 0; i < lenBy; i++)
    {
      if(!isspace(field2[i]))
      {
        // 改行フラグが立っているなら
        if(k == 1)
        {
          // 各種、何個前がスペースだったか判定、処理
          if(isspace(field2[i - 3]))
          {
            i = i - 2;
          }else if(isspace(field2[i - 4])){
            i = i - 3;
          }else if(isspace(field2[i - 6])){
            i = i - 5;
          }
          
          // 改行フラグ初期化
          k = 0;
        }
        
        // 印字可能文字かを判定、可能であれば書き込み
        if(isprint(field2[i]))
        {
          fprintf(out_file,"%c",field2[i]);
        }
      }else{
        j++;
        
        // スペースが2回出てきたら
        if(j == 2)
        {
          // 改行を書き込み
          fprintf(out_file,"%s","\n");
          j = 0;
          
          // 改行したフラグ
          k = 1;
        }
      }
    }
    
    //音素数を算出
    sumUni++;
  }

  // close
  fclose(in_file2);
  fclose(out_file);
  
  // systemでコマンド実行、バイグラムの頻度を算出してファイルに書き込む
  system(cmd3);
  
  // fopenでバイグラムとその頻度が記述されているファイルを読み込む
  if((in_file2 = fopen("nlp_pri_f2.txt","r")) == NULL)
  {
    printf(" cannot open out pipe!!");
    exit(0);
  }

  // fopenで書き込み用ファイルオープン
  if((out_file = fopen("bigram_pri.txt","w")) == NULL)
  {
     fprintf(stderr,"WRITE FILE ERROR !!");
     exit(0);
  }

  // ユニグラムのファイル(in_file)から読み込んだ音素と該当するものを
  // バイグラムのファイル(in_file2)から見つけ出してfprintfで確率(を算出し、それ)と共に書き込む
  // また、バイグラムのファイルについては文頭の"E"を追加していたため、
  // "E"の場合、判定されないため、そのためのifも記述
  while((fgets(field,80,in_file)) != NULL)
  {
    sscanf(field,"%lf %s",&nowFreq,priPhoneme);

    while((fgets(field2,80,in_file2)) != NULL)
    {
      sscanf(field2,"%lf %s",&nowFreq2,priPhoneme2);

      // strstrで該当文字の位置を算出し、0番目ならば書き込み
      // また、例として"tsu"は"ts"についての処理を行いたいが、"t"の場合でもstrstrでは0が返ってきて処理されてしまうため、
      // それを避ける条件式を記述
      if((strstr(priPhoneme2,priPhoneme) - priPhoneme2) == 0 && !(strlen(priPhoneme) == 1 && strlen(priPhoneme2) > 2))
      {
        printf("%d  %.0f　　　\t / %.0f　　　\t%s\n",i,nowFreq2,nowFreq,priPhoneme2);
        fprintf(out_file,"%.0f %.3f %s\n",nowFreq2,(nowFreq2 / nowFreq),priPhoneme2);
      }else if((strstr(priPhoneme2,"E") - priPhoneme2) == 0){
        printf("%d  %.0f　　　\t / %.0f　　　\t%s\n",i,nowFreq2,sumUni,priPhoneme2);
        fprintf(out_file,"%.0f %.3f %s\n",nowFreq2,(nowFreq2 / sumUni),priPhoneme2);
      }
    }
    
    // rewindでファイルポインタの位置を先頭に戻す
    rewind(in_file2);
  }
  
  // close
  pclose(in_file2);
  fclose(in_file);
  fclose(out_file);
  
  return 0;
}
