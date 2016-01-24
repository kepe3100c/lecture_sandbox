#include <stdio.h>
#include <string.h>

FILE *fp,*fp2;

int main()
{
  char field[81];  // fgetsで一時的に1行入れる用
  char domi[50];
  char chun[2][10];
  int i = 0,j = 0,k =0,l = 0,m = 0;
  int len;
  fpos_t pos;
    
  if((fp = fopen("char.txt","r")) == NULL)
  {
     fprintf(stderr,"READ FILE ERROR !!");
     exit(0);
  }
  
  if((fp2 = fopen("chacha.txt","w")) == NULL)
  {
     fprintf(stderr,"READ FILE ERROR !!");
     exit(0);
  }

  while((fgets(field,80,fp)) != NULL)
  {
    printf("%s\n",field);
  }
  
  fgetpos( fp, &pos );
  
  printf("%d\n",pos);
  
  // rewind(fp);
  
  fgetpos( fp, &pos );
  
  printf("%d\n",pos);
  
  while((fgets(field,80,fp)) != NULL)
  {
    printf("%s\n",field);
  }
  
  fclose(fp);
  fclose(fp2);
}
