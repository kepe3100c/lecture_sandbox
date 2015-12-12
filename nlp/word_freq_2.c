#include <stdio.h>

int sort()
{
 char command[50];
 char field[81];
 char field2[81];
 FILE *in_file,*in_file2, *out_file;
 char *cmd = "sort kadai_25_r.txt | grep '名詞' | uniq -c | sort -r | sed -e 's/^[ ]*//g' | grep -v '1' | sed 's/[名詞]//g' | awk '{print $2 " " $1}'";

 if(!(in_file=popen(cmd,"r"))){
   printf(" cannot open out pipe!!");
   exit(0);
 }

 //if(!(in_file2=popen("grep 'ﾌｾｻ・","r"))){
 //  printf(" cannot open out pipe!!");
 //  exit(0);
 // }


 if(!(out_file=popen("awk '{print $2 " " $1}'","w"))){
   printf(" cannot open in pipe!!");
   exit(0);
 }
 //while((fgets(field,80,in_file))!=NULL){
 //  fputs(field,in_file2);
 //  printf("aha");
 //}

 while((fgets(field,80,in_file)) != NULL){
   fputs(field,out_file);
 }

 pclose(in_file);
 //pclose(in_file2);
 pclose(out_file);

 return 0;
}


int main(void){
  
  sort();
  
  
  return 0;
}