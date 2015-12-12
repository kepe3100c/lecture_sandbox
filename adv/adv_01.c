/********************************************************************/
/*                                                                  */
/*  知能システム演習Ⅱ 進化計算                                     */
/*    第1回課題  関数最大値探索問題                                 */
/*                                          0312013139 村上 啓      */
/*                                              提出日: 2015/10/10  */
/*                                                                  */
/********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>   // 乱数初期化用

// #define PI 3.141592 // 円周率π
#define MAXRAND1 10  // 乱数の最大値(親用)
#define MAXRAND2 1024  // 乱数の最大値(初期配列用)

static int parentsTag[10];  // 親の組み合わせ格納用


/*****************\
| qsort用比較関数 |
\*****************/
float float_sort( const void * a , const void * b ) {
  /* 引数はvoid*型と規定されているのでint型にcastする */
  if( *( float * )a < *( float * )b ) {
    return -1;
  }
  else
  if( *( float * )a == *( float * )b ) {
    return 0;
  }
  return 1;
}


/**********************\
| 親の組み合わせ用関数 |
\**********************/
int randomParents(void) {

	int iaRandarray[MAXRAND1];   // 乱数候補収納用変数
	int iCounter;   // ループカウンタ用変数
	int iNumRand;   // 残り乱数候補数
	int iRandKey;   // 乱数候補取得用変数
	int iRandVal;   // 乱数の取得用変数
	
	// 乱数の種を初期化
	srand(time(NULL));

	// あらかじめ配列に数値を代入しておく
	for (iCounter = 0; iCounter < MAXRAND; iCounter++) {
		iaRandarray[iCounter] = iCounter;
	}

	// 
	iNumRand = MAXRAND1;
	for (iCounter = 0; iCounter < MAXRAND; iCounter++) {

		// 乱数取得
		iRandKey = rand();

		// 取得した乱数を残り配列で割った余りを取得する
		iRandKey %= iNumRand;

		// 配列の中身を乱数として取得する
		iRandVal = iaRandarray[iRandKey];

		// つかった乱数を未使用の乱数で置き換える
		iaRandarray[iRandKey] = iaRandarray[iNumRand - 1];

		// 乱数候補を一つ減らす
		--iNumRand;
		
		// 格納
		parentsTag[iCounter] = iRandVal;
		
		// テスト用表示
		// printf("%d,", parentsTag[iCounter]);
		
	}

	// 体裁を整える改行出力
	// printf("\n");

}


/************\
| 適応度計算 |
\************/
int fitnessCal(float cal)
{
  float precal1 = 0.0,precal2 = 0.0;  // 途中計算用
  float value = 2; 
	
	// 以下で適合度を計算
	for(i = 0; i < value; i++){
	  precal1 += 0.5 * sin( (cal1 * PI) / 1024 ) * cos( (20 * cal1 * PI) / 1024 ) + 0.5;
  }
  
  for(i = 0; i < value; i++){
    precal2 += 0.5 * sin( (cal2 * PI) / 1024 ) * cos( (20 * cal2 * PI) / 1024 ) + 0.5;
  }

  f1 = (1 / value) * precal1;
  f2 = (1 / value) * precal2;
	
	return cal;
}


/******\
| main |
\******/
int main(void)
{
  float chroms[10][2]  // 染色体用配列
  
	int i;  // loop counter
  
  // 乱数の種を初期化
	srand(time(NULL));
	
	// 染色体初期値
	for(i = 0; i < 10; i++)
	{
	  chroms[i][0] = rand() % SIZE;
	}
	
	// 適合度計算
	for(i = 0;i < 10;i++)
	{
	  chroms[i][1] = fitnessCal(chroms[i][0]);
	}
	
	
	// randomParents();    // 親の組み合わせ
	
	// 親の組み合わせ確認テスト用表示
	// for(i = 0; i < 10; i++) {　printf("%d,",parentsTag[i]); } printf("\n");
	
	//qsort();
	
}
