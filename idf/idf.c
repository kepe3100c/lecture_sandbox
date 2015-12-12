#include <stdio.h>
#include <string.h>
#include <math.h>

FILE *fr1,*fw;
char *fn[5] = {"a_r.txt","b_r.txt","c_r.txt","d_r.txt","e_r.txt"};  //�ե�����̾(.txt��)

int sort(void){
  char buff[100];  //�¹Է��̼��Ϥ���(fgets�Ǽ����Ϥ�)
  char cmb[200];  //���ޥ��ɷ�����
  char *cmd1 = "sed -e 's/ *$//g' > pre_sort.txt";  //��������
  char *cmd2 = "sed -e 's/ *$//g' >> pre_sort.txt";  //�ɵ���
  int i;  //loop counter
  int cmb_len = strlen(cmb);  //memset��
  
  for(i = 0;i < 5;i++){
    
    //���ޥ��ɷ���
    sprintf(cmb,"sort %s | grep '̾��' | uniq | sed -e 's/^[ ]*//g' | sed 's/[̾��]//g'",fn[i]);
    
    //fr1��cmd1�¹Է��̤���Ǽ(popen)
    if(!(fr1=popen(cmb,"r"))){
      printf(" cannot poepn read !");
      exit(0);
    }
    
    //�����ܰʹߤ��ɵ�
    if(i == 0){
      //fw��fr1���˹Ԥ���������
      if(!(fw=popen(cmd2,"w"))){
	printf("cannot popen write !");
	exit(0);
      }
    }else{
      if(!(fw=popen(cmd3,"w"))){
	printf("cannot popen write !");
	exit(0);
      }
    }
    
    //fgets��fr1�����Ƥ�fw���Ϥ�
    while((fgets(buff,80,fr1)) != NULL){
      fputs(buff,fw);
    }
    
    //pclose
    pclose(fr1);
    pclose(fw);
    
    //���祳�ޥ��ɽ�����
    memset(cmb,'\0',cmb_len);
    
  }

  system("uniq pre_sort.txt > w_sort.txt");
  
  return 0;
}


int idf(void){
  
  char w_buff1[20];  //ñ��������Ǽ�ѡ�w_sort.txt��
  char w_buff2[20];  //ñ��������Ǽ�ѡ��о�ʸ��5�ե�������
  char *word[400];  //5�ե�����ʬ��̾�쥽����ñ����Ǽ��
  int *tf[400];  //tf�ͳ�Ǽ��
  int i = 0,j = 0,k=0;  //��������

  //�ե����륪���ץ���w_sort.txt����
  if((fr1 = fopen("w_sort.txt","r")) == NULL){
    fprintf(stderr,"READ FILE OPEN ERROR !!");
    exit(0);
  }

  //fscanf��ñ�������С�word�����˳�Ǽ
  while((fscanf(fr1,"%s",&w_buff1)) != NULL){
    printf("%s",w_buff1);
    fprintf(word,"%s",w_buff1);
    i++;
  }

  for(j = 0;j < 5;j++){

    //
    if((fr2 = fopen(fn[i],"r")) == NULL){
      fprintf(stderr,"READ FILE OPEN ERROR !!");
      exit(0);
    }
    
    //fscanf��ñ��������
    while((fscanf(fr2,"%s",&w_buff2)) != NULL){
      for(k = 0;k < i;k++){
	if(strstr(w_buff2,word[k]) != NULL){
	  tf[k]++;
	}
      }
    }
    
    

    fclose(fr2);
  }
  
  return 0;
}


int main(void){
  sort();
  
  return 0;
}
