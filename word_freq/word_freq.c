#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fr,*fw;

int main()
{

  char noun[] = "̾��";  //̾��Ƚ����
  char *pri;  //̾��Ƚ����
  char *n_pri;  //
  char pp[400];
  char n_list_f[400];  //�ǽ���Ǽ��
  char *num;  //̾��Ƚ��if������ʸ�ˡ�̾��ɤȤ���ʸ�������ä�����Ƚ�������
  int i = 0,j = 0;  //loop counter

  //�ɤ߹��ߥե����륪���ץ�
  if((fr = fopen("kadai_25_r.txt","r")) == NULL){
    fprintf(stderr,"READ FILE ERROR !!");
    exit(0);
  }

  //�񤭹��ߥե����륪���ץ�
  if((fw = fopen("kadai_25_rr.txt","w")) == NULL){
    fprintf(stderr,"WRITE FILE ERROR !!");
    exit(0);
  }
  
  //1�Ԥ���fgets���ɤ߹���
  //

  printf("ababa\n");
  
  while(fgets(pp,400,fr) != NULL){
    pri = strstr(pp,noun);
    if(pri != NULL){
      n_list_f[j] = pp[i];
      j++;
      i++;
    }else{
      i++;
    }
  }
  
  
  for(i = 0;i < 19;i++){
    printf("%s\n",n_list_f[i]);
  }
  
  
  
  return 0;
}
