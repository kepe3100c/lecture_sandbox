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
    // sscanf(field,"%s",domi);
    
    len = strlen(field);
    
    for(i = 0; i < len; i++)
    {
      if(!isspace(field[i]))
      {
        if(k == 1)
        {
            if(isspace(field[i - 3]))
            {
              i = i - 2;
            }else if(field[i - 4]){
              i = i - 3;
            }
          k = 0;
        }
        if(isprint(field[i]))
        {
          fprintf(fp2,"%c",field[i]);
          // m++;
        }
        // printf("%c\n",field[i]);
      }else{
        j++;
        if(j == 2)
        {
          fprintf(fp2,"%s","\n");
          j = 0;
          k = 1;
        }
      }
    }
    // l++;
  }
  
  for(i = 0; i < 2; i++)
  {
    for(j = 0; j < 10; j++)
    {
      // printf("%c",chun[i][j]);
    }
  }
  
  fclose(fp);
  fclose(fp2);
}
