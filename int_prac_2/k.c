#include <stdio.h>
#include <stdlib.h>

FILE *fp;  // ファイルポインタ

int main(void){
  
  char field[50];  // fgetsで1行格納用
  double xrange[400],yrange[400];  // x、y格納用
  int i,j;  // counter
  
  // fopenで開く
  if((fp = fopen("k.txt","r")) == NULL)
  {
    fprintf(stderr,"READ FILE ERROR !!");
    exit(0);
  }
  
  // fgets
  while((fgets(field,80,fp)) != NULL)
  {
    sscanf(field,"%lf   %lf   %lf",&xrange[i],&yrange[i],&clas[i]);
  }
  
  
  
  
  
  
  return 0;
}
