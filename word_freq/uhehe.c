#include <stdio.h>
#include <string.h>

int main()
{
  //処理順に解説
  const char *cmd = "sort kadai_25_r.txt | grep '名詞' | uniq -c | sort -r | sed -e 's/^[ ]*//g' | grep -v '1' | sed 's/[名詞]//g'| awk '{print $2 $1}'";

  char *fn[5] ={"a","b","c","d","e"};
  char cmb[500];
  int i,j=strlen(cmb);
    
  for(i = 0;i < 5 ;i++){
    sprintf(cmb,"sort %s.txt | grep '名詞' | uniq -c | sort -r | sed -e 's/^[ ]*//g' | grep -v '1' | sed 's/[名詞]//g'| awk '{print $2 $1}'",fn[i]);
    puts(cmb);
    memset(cmb,'\0',j);
  }  

  return 0;
}

