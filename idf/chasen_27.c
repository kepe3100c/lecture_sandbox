/* chasen_test.c: student.txt を単語分割し，student_r.txt に出力する */
#include <stdio.h>
/* 茶筌ヘッダファイルをインクルード */
#include "/usr/local4/chasen/include/chasen.h"

int main()
{
	/* 茶筌のオプションを設定 */
	/* オプションについては，茶筌のマニュアルも参照のこと．*/
  char *option[]={"chasen_27", "-F", "%m %H\n", NULL};
	FILE *fp_in, *fp_out;

	/* chasen オプション指定 */
	if(chasen_getopt_argv(option, stderr) != 0)
		return -1;

	/* 入力ファイルオープン */
	fp_in = fopen("e.txt", "r");
	if (fp_in == NULL){
		fprintf(stderr, "Cannot open file: a.txt\n");
		return -1;
	}

	/* 出力ファイルオープン */
	fp_out = fopen("e_r.txt", "w");
	if (fp_out == NULL){
		fprintf(stderr, "Cannot open file: a_r.txt\n");
		return -1;
	}

	/* 茶筌関数実行 */
	if(chasen_fparse(fp_in, fp_out) != 0){
		fprintf(stderr, "chasen_fparse error!!\n");
		return -1;
	}
	printf("a_r.txt への出力終了\n");

	fclose(fp_in);
	fclose(fp_out);

	return 0;
}

/*
コンパイル（ライブラリ libchasen.a をリンク）
$ cc -o chasen_test chasen_test.c -L/usr/local4/chasen/lib -lchasen

環境変数の設定
$ LD_LIBRARY_PATH=/usr/local4/chasen/lib
$ export LD_LIBRARY_PATH
（.bashrc で設定すれば，次回以降設定不要）
*/
