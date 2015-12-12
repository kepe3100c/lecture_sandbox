#include <stdio.h>
#include <time.h>

/*乱数の最大値*/
#define MAXRAND 10

int randomcc(void) {

    int iaRandarray[MAXRAND]; /*乱数候補収納用変数*/
    int iCounter; /*ループカウンタ用変数*/
    int iNumRand; /*残り乱数候補数*/
    int iRandKey; /*乱数候補取得用変数*/
    int iRandVal; /*乱数の取得用変数*/

    /*乱数の種を初期化*/
    //srand(time(NULL));

    /*あらかじめ配列に数値を代入しておく*/
    for (iCounter = 0; iCounter < MAXRAND; iCounter++) {
        iaRandarray[iCounter] = iCounter;
    }

    /*テスト用ループ*/
    iNumRand = MAXRAND;
    for (iCounter = 0; iCounter < MAXRAND; iCounter++) {

        /*乱数を取得*/
        iRandKey = rand();

        /*取得した乱数を残り配列で割った余りを取得する*/
        iRandKey %= iNumRand;

        /*配列の中身を乱数として取得する*/
        iRandVal = iaRandarray[iRandKey];

        /*つかった乱数を未使用の乱数で置き換える*/
        iaRandarray[iRandKey] = iaRandarray[iNumRand - 1];

        /*乱数候補を一つ減らす*/
        --iNumRand;

        /*テスト用表示*/
        printf("%d,", iRandVal);

    }

    /*体裁を整える改行出力（本質ではない）*/
    printf("\n");


}

int main(void)
{
    int i; // loop counter
        srand(time(NULL));
    for(i = 0; i < 10; i++)
    {
        randomcc();
    }
}