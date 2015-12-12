/********************************************************************/
/*                                                                  */
/*  知能システム演習Ⅱ 進化計算                                     */
/*    第1回課題  関数最大値探索問題(ルーレット選択、期待値選択)     */
/*                                          0312013139 村上 啓      */
/*                                              提出日: 2015/10/19  */
/*                                                                  */
/********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h> // 乱数初期化用

#define PI 3.141592 // 円周率π
#define ROUND_ANGLE 360 // 円周角、ルーレットの個体選択時にも使用
#define MAXRAND1 10 // 乱数の最大値(親用)
#define MAXRAND2 1048576 // 乱数の最大値、1024*1024(染色体長(10*2)分)


/************\
| 適合度計算 |
\************/
float fitnessCal(int cal)
{
    float precal1 = 0,precal2 = 0;  // 途中計算用
    float value = 2; // nの値
    float f1,f2,f3;  // 適合度格納用
    double chromosome_f = 0,chromosome_r = 0;	// 染色体、前半分、後ろ半分
    double base = 0;  // 10進数変換用、べき乗の値
    double chromosome[20]; // 染色体
    int i = 0; // loop counter

    for (i = 0; i < 20; i++) { chromosome[i] = 0; } // 初期化

    // 2進数変換
    for (i = 0; i < 20; i++)
    {
        chromosome[i] = cal % 2;
        cal = cal / 2;
    }
    
    // 前半分と後ろ半分に分けつつ10進数変換
    for(i = 0; i < 20; i++)
    {
        if(i < 10)
        {
            chromosome_r += pow((chromosome[i] * 2),base);
            base++;
            if(i == 9){ base = 0;}  // べき乗リセット
        }else{
            chromosome_f += pow((chromosome[i] * 2),base);
            base++;
        }
    }

    // 以下で適合度を計算
    for (i = 0; i < value; i++)
    {
        precal1 += 0.5 * sin((chromosome_f * PI) / 1024) * cos((20 * chromosome_f * PI) / 1024) + 0.5;
    }

    for (i = 0; i < value; i++)
    {
        precal2 += 0.5 * sin((chromosome_r * PI) / 1024) * cos((20 * chromosome_r * PI) / 1024) + 0.5;
    }

    f1 = (1 / value) * precal1;
    f2 = (1 / value) * precal2;
    
    // 最終的な適合度
    f3 = (f1 + f2) / 2;
    
    // 最終的な適合度を返す
    return f3;
}


/****************\
| ルーレット選択 |
\****************/
double roulette(double cal,double sum_fitness)
{
    double sp;    // 選択確率
    double angle; // 角度
    int i;  // loop counter
    
    // 選択確率を計算
    sp = cal / sum_fitness;
    
    // 角度を計算
    angle = ROUND_ANGLE * sp;
    angle = floor(angle);
   
    return angle;
}


/************\
| 期待値選択 |
\************/
double expected(double cal,double sum_fitness)
{
    double sp;    // 選択確率
    double ex_rep_value; // 期待値及び再生数用
    int i;  // loop counter
    
    // 選択確率を計算
    sp = cal / sum_fitness;
    
    // 期待値を計算
    ex_rep_value = sp * 10;
    
    // 四捨五入
    if(ex_rep_value > 0.0)
    {
        return floor(ex_rep_value + 0.5);
    }else{
        return -1.0 * floor(fabs(ex_rep_value) + 0.5);
    }
}


/******\
| main |
\******/
int main(void) 
{
    double chromosome[10][5]; // 染色体用配列
    double chromosome_bin[10][20]; // 染色体2進数変換後用
    double sum_fitness = 0; // 適合度合計
    double angles[10];   // 角度格納配列
    double random_angle;   // 個体選択用乱数
    int bin;  // 2進数変換用
    int i,j; // loop counter

    // 乱数の種を初期化
    srand(time(NULL));

    for(i = 0; i < 10; i++){ chromosome[i][1] = 0; chromosome[i][3]; for(j = 0; j < 20; j++){ chromosome_bin[i][j] = 0;} }  // 適合度、選択回数、2進数変換後染色体初期化

    // 染色体初期値
    for(i = 0; i < 10; i++)
    {
        chromosome[i][0] = rand() % MAXRAND2;
    }

    // 適合度計算
    for(i = 0; i < 10; i++)
    {
        chromosome[i][1] = fitnessCal(chromosome[i][0]);
        sum_fitness += chromosome[i][1];
    }
    
    // ルーレット選択(角度計算)
    for(i = 0; i < 10; i++)
    {
        chromosome[i][2] = roulette(chromosome[i][1],sum_fitness);
        angles[i] = chromosome[i][2];
    }
        
    // ルーレット選択(個体選択)
    for(i = 0; i < 10; i++)
    {
        // 個体選択用乱数取得
        random_angle = rand() % ROUND_ANGLE;
        
        for(j = 0; j < 10; j++)
        {
            // どの時点で個体選択用乱数を超えたか、
            // 超えた場合(負の値の時)は1つ前の染色体が選択される
            random_angle -= angles[j];
            if(random_angle < 0)
            {
                if(j == 0)
                {
                    // 範囲外に出ないようにする
                    chromosome[j][3]++;
                }else{
                    chromosome[j-1][3]++;
                }
                j = 10;
            }else if(j == 9){
                // 角度の値を丸める仕様上、全染色体の角度を引いても
                // 個体選択用乱数が負にならない場合が存在するため、
                // その時は最後の染色体が選択される
                chromosome[j][3]++;
            }
        }
    }
    
    // 期待値選択
    for(i = 0; i < 10; i++)
    {
        chromosome[i][4] = expected(chromosome[i][1],sum_fitness);
    }
    
    // 2進数変換
    for (i = 0; i < 10; i++)
    {
        
        bin = chromosome[i][0];
        for(j = 0; j < 20; j++)
        {
            chromosome_bin[i][j] = bin % 2;
            bin = bin / 2;
        }
    }
    
    // 確認用
    printf("+-------------------------------------------------------------------------------------------------------------------------------------+\n");
    for(i = 0; i < 10; i++)
    {   printf("| chromosome %d   : ",i);
        for(j = 0; j < 20; j++){
            printf("%.0f",chromosome_bin[i][19 - j]);
        }
        printf(" | %.0f    | Fittness value -> %.3f   | Angle -> %.0f  | Roulette RN -> %.0f  | Expected RN -> %.0f |\n",chromosome[i][0],chromosome[i][1],chromosome[i][2],chromosome[i][3],chromosome[i][4]);
    }
    printf("+-------------------------------------------------------------------------------------------------------------------------------------+\n");

}
