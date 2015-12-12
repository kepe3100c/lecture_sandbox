#include <stdio.h>
#include <string.h>
#include <math.h>

FILE *fr1,*fr2,*fw;



int main(void)
{
 char command[50];
 char buff[100];  //実行結果受渡し用(fgetsで受け渡す)
 char *fn[5] = {"a","b","c","d","e"};  //ファイル名(a,b,c,d,e)
 char cmb[200];  //コマンド結合用
 char *cmd1 = "sort kadai_25_r.txt | grep '名詞' | uniq -c | sort -r | sed -e 's/^[ ]*//g' | grep -v '1' | sed 's/[名詞]//g' | awk '{print $2 " " $1}'";
 char *cmd2 = "awk '{print $2 " " $1}' > rrr.txt";
 char *cmd3 = "awk '{print $2 " " $1}' >> rrr.txt";
 int i;  //loop counter
 int cmb_len = strlen(cmb);

 for(i = 0;i < 1;i++){
   
   //コマンド結合
   sprintf(cmb,"sort %s.txt | grep '名詞' | uniq -c | sort -r | sed -e 's/^[ ]*//g' | grep -v '1' | sed 's/[名詞]//g' | awk '{print $2 " " $1}'",fn[i]);

   printf("1\n");

   //fr1にcmd1実行結果を格納(popen)
   if(!(fr1=popen(cmb,"r"))){
     printf(" cannot poepn read !");
     exit(0);
   }

   //一回目以降は追記
   if(i == 0){
     //fwにfr1後に行いたい処理
     if(!(fw=popen(cmd2,"w"))){
       printf(" cannot popen write !");
       exit(0);
     }
   }else{
     if(!(fw=popen(cmd3,"w"))){
       printf(" cannot popen write !");
       exit(0);
     }
   }

   //fgetsでfr1の内容をfwに渡す
   while((fgets(buff,80,fr1)) != NULL){
     fputs(buff,fw);
   }

   //pclose
   pclose(fr1);
   pclose(fw);
   
   
   //結合コマンド初期化
   memset(cmb,'\0',cmb_len);


 }

 return 0;
}

/*
 *int main(void){
 * 
 *  sort();
 *
 *return 0;
 *}
 */
