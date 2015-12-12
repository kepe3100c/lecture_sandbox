/* chasen_test.c: student.txt ��ñ��ʬ�䤷��student_r.txt �˽��Ϥ��� */
#include <stdio.h>
/* ��䥥إå��ե�����򥤥󥯥롼�� */
#include "/usr/local4/chasen/include/chasen.h"

int main()
{
	/* ��䥤Υ��ץ��������� */
	/* ���ץ����ˤĤ��Ƥϡ���䥤Υޥ˥奢��⻲�ȤΤ��ȡ�*/
  char *option[]={"chasen_27", "-F", "%m %H\n", NULL};
	FILE *fp_in, *fp_out;

	/* chasen ���ץ������� */
	if(chasen_getopt_argv(option, stderr) != 0)
		return -1;

	/* ���ϥե����륪���ץ� */
	fp_in = fopen("e.txt", "r");
	if (fp_in == NULL){
		fprintf(stderr, "Cannot open file: a.txt\n");
		return -1;
	}

	/* ���ϥե����륪���ץ� */
	fp_out = fopen("e_r.txt", "w");
	if (fp_out == NULL){
		fprintf(stderr, "Cannot open file: a_r.txt\n");
		return -1;
	}

	/* ��䥴ؿ��¹� */
	if(chasen_fparse(fp_in, fp_out) != 0){
		fprintf(stderr, "chasen_fparse error!!\n");
		return -1;
	}
	printf("a_r.txt �ؤν��Ͻ�λ\n");

	fclose(fp_in);
	fclose(fp_out);

	return 0;
}

/*
����ѥ���ʥ饤�֥�� libchasen.a ���󥯡�
$ cc -o chasen_test chasen_test.c -L/usr/local4/chasen/lib -lchasen

�Ķ��ѿ�������
$ LD_LIBRARY_PATH=/usr/local4/chasen/lib
$ export LD_LIBRARY_PATH
��.bashrc �����ꤹ��С�����ʹ��������ס�
*/
