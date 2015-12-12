/********************************************************************/
/*                                                                  */
/*  知能システム演習Ⅱ 進化計算                                     */
/*    第1回課題  関数最大値探索問題(1点交叉、多点交叉)              */
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

static double crossoverd_children[2];  // 交叉後生成子

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


/**************************\
| ルーレット選択(角度計算) |
\**************************/
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


/**********\
| 一点交叉 |
\**********/
double op_crossover(int cal1,int cal2)
{
    double chromosome1[20],chromosome2[20]; // 染色体2進数変換後格納用
    double crossovers;  // 交叉配列一時格納用
    double base; // 10進数変換用
    int i;  // loop counter
    
    // 初期化
    crossoverd_children[0] = 0;
    crossoverd_children[1] = 0;
    base = 0;
    
    // 2進数変換
    for(i = 0; i < 20; i++)
    {
        chromosome1[i] = cal1 % 2;
        chromosome2[i] = cal2 % 2;
        cal1 = cal1 / 2;
        cal2 = cal2 / 2;
    }
    
    // 交叉処理
    for(i = 0; i < 8; i++)
    {
        crossovers = chromosome1[i];
        chromosome1[i] = chromosome2[i];
        chromosome2[i] = crossovers;
    }

    // 10進数で値を返す
    for(i = 0; i < 20; i++)
    {
        crossoverd_children[0] += pow((chromosome1[i] * 2),base);
        crossoverd_children[1] += pow((chromosome2[i] * 2),base);
        base++;
    }
}


/******\
| main |
\******/
int main() 
{
    double chromosome[10][4]; // 染色体用配列
    double chromosome_bin[10][20]; // 染色体2進数変換後用
    double sum_fitness = 0; // 適合度合計
    double angles[10];   // 角度格納配列
    double random_angle;   // 個体選択用乱数
    double crossover_p;  // 交叉実行確率用乱数
    int choise_parents[2];   // ルーレット選択後の選択された親
    int bin;  // 2進数変換用
    int ichoise = 0;  // 交叉前選択染色体判別処理用カウンター
    int icrossover;  // 交叉用ループカウンター
    int crosscount = 0;  // 交叉回数
    int selection_p = 0;  // 自然淘汰時選択子ランダム用
    int selection_p2 = 0; // 自然淘汰時選択確率
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
    int fitness(){
        // 初期化
        sum_fitness = 0;
        for(i = 0; i < 10; i++)
        {
            chromosome[i][1] = fitnessCal(chromosome[i][0]);
            sum_fitness += chromosome[i][1];
        }
    }
    // 初期染色体適合度計算実行
    fitness();
    
    // ルーレット選択(角度計算)
    int roulette_angle()
    {
        for(i = 0; i < 10; i++)
        {
            chromosome[i][2] = roulette(chromosome[i][1],sum_fitness);
            angles[i] = chromosome[i][2];
        }
    }
    // 初期染色体角度計算実行
    roulette_angle();

    // ルーレット選択関数(個体選択)
    int roulette_choise(){
        // 初期化
        for(i = 0; i < 10;i++){chromosome[i][3] = 0;}
        
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
                    chromosome[9][3]++;
                }
            }
        }
    }
    // 初期染色体ルーレット選択実行
    roulette_choise();
    
    // 交叉用親選択
    int parents(){
        choise_parents[0] = -1;
        choise_parents[1] = -2;
        ichoise = 0;
        for(i = 0; i < 10; i++)
        {
            for(j = 0; j < 10; j++)
            {
                if(chromosome[j][3] >= 9 - i)
                {
                    // 親が2個以上選択されているならループ終了
                    if(ichoise > 1){ i = 10; j = 10; break; }
               
                    // 現在の走査している染色体の番号を親として入れる
                    choise_parents[ichoise] = j;
                    
                    // 現在の走査している染色体の番号が既に選択されているならばbreak
                    // そうでなければ選択された親の数を増加
                    if(ichoise > 0 && choise_parents[0] == choise_parents[1])
                    {
                        // break;
                    }else{
                        ichoise++;
                    }
                }
            }
        }
    }
    // 初期染色体親選択実行
    parents();
    
    // 自然淘汰処理
    int natural_selection()
    {
        for(i = 0; i < 10; i++)
        {
            if(chromosome[i][3] == 0)
            {
                // 再生数が0のものが1/5の確率で淘汰
                selection_p2 = rand() % 5;
                if(selection_p2 > 0){break;}
                
                selection_p = rand() % 2;
                chromosome[i][0] = crossoverd_children[selection_p];
            }
        }
    }
    
    // 確認表示用
    int confirmation(int gf)
    {
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
        printf("\n");

        if(gf == 0)
        {
            printf("+---------+\n| Genesic |\n");
            printf("+---------+---------------------------------------------------------------------------------------------------------+\n");
        }else{
            printf("+---------------------------------------+\n| %d Generation | Crossover Count : %d |\n",icrossover,crosscount);
            printf("+---------------------------------------+---------------------------------------------------------------------------+\n");
        }
        
        for(i = 0; i < 10; i++)
        {   
            printf("| chromosome %d  : ",i);
            for(j = 0; j < 20; j++){
                printf("%.0f",chromosome_bin[i][19 - j]);
            }
            printf(" | %.0f    | Fittness value -> %.3f   | Angle -> %.0f  | Roulette RN -> %.0f  |\n",chromosome[i][0],chromosome[i][1],chromosome[i][2],chromosome[i][3]);
        }
        printf("+-------------------------------------------------------------------------------------------------------------------+\n\n");
    }
    // 初期染色体確認
    confirmation(0);
    
    // 任意の世代数実行
    for(icrossover = 0; icrossover < 100; icrossover++)
    {
        // 交叉実行確率用乱数取得
        crossover_p = rand() % 3;
        
        // 1/3の確率で交叉実行
        if(crossover_p > 1)
        {
            // 交叉回数
            crosscount++;
            // printf("Do Crossover Generation : %d\n",icrossover);

            op_crossover(chromosome[choise_parents[0]][0],chromosome[choise_parents[1]][0]);
            natural_selection();
            
            fitness();
            roulette_angle();
            roulette_choise();      

            parents();
        
        }
    }
    
    // 50世代後確認
    confirmation(1);
}
