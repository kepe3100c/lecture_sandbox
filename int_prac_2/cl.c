#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

//出力するのはクラス1のノードの組み合わせとクラス2のノードの組み合わせ
int main() {
    //データ数 = リンク数       28
    //次元数(要素数) = ノード数 16
    int data[28][16];
    FILE *fp;
    
    int node1=0;
    int node2=0;
    int ret;
    int a=0;
    int b=0;
    double c1=0;
    double c2=0;
    int end_flag=0;
    double learn_w = 0.1;
    double learn_l = 0.01;
    double o1[16];  //初期生成点クラス1
    double o2[16];  //初期生成点クラス2
    double set1[16];//一時記憶用
    double set2[16];//一時記憶用
    int clas[26];//クラス指定用
    int clas1=0; //クラス1のノード数
    int clas2=0; //クラス1のノード数
    
    char *fname = "CL.data";
    fp = fopen( fname, "r" );
    if( fp == NULL ){
        printf( "%sファイルが開けません\n", fname );
        return -1;
    }
    while( ( ret = fscanf( fp, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d" ,&data[a][0],&data[a][1],&data[a][2],&data[a][3],&data[a][4],&data[a][5],&data[a][6],&data[a][7],&data[a][8],&data[a][9],&data[a][10],&data[a][11],&data[a][12],&data[a][13],&data[a][14],&data[a][15])) != EOF){
        // printf("%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n", data[a][0], data[a][1], data[a][2], data[a][3], data[a][4], data[a][5], data[a][6], data[a][7], data[a][8], data[a][9], data[a][10], data[a][11], data[a][12], data[a][13], data[a][14], data[a][15]);
        a++;
    }
    fclose( fp );
    
    node1 = 0;
    node2 = 1;
    while(node1 != node2) {    //ノードの数が等しければ終了
        node1=0;
        node2=0;
        //初期点をランダムで生成
        srand(time(NULL));
        for(a=0;a<16;a++){
            o1[a] = rand() %20;
            o2[a] = rand() %20;
        }
        ////////////////////////
        
        //値が変動しなくなったら終了する
        while(end_flag == 0){
            end_flag = 0;
            //全データで試行する
            //あらかじめ値を記録しておく
            for(b=0;b<16;b++){
                set1[b] = o1[b];
                set2[b] = o2[b];
            }
            for(a=0;a<26;a++){
                //入力は2つ(2分割なので)
                double sum1=0;
                double sum2=0;
                for(b=0;b<16;b++){  //全特徴(16)から距離を出力
                    //√(( - )^2) ⇒ 距離  どちらの点に近いか判別
                    sum1 += pow(o1[b] - data[a][b],2);
                    sum2 += pow(o2[b] - data[a][b],2);
                }
                sum1 = sqrt(sum1);  //距離1
                sum2 = sqrt(sum2);  //距離2
                
                //近い方は学習する（距離はどのように計算する?）
                if(sum1 < sum2){   //sum1 => sum2
                    //sum1が学習する(o1)
                    for(b=0;b<16;b++){
                        o1[b] = o1[b] + learn_w*(data[a][b]-o1[b]);
                        o2[b] = o2[b] + learn_l*(data[a][b]-o2[b]);
                    }
                } else {//sum1 > sum2
                    //sum2が学習する(o2)
                    for(b=0;b<16;b++){
                        o2[b] = o2[b] + learn_w*(data[a][b]-o2[b]);
                        o1[b] = o1[b] + learn_l*(data[a][b]-o1[b]);
                    }
                }  
                
                //現データを記憶しておいた値と比較する
                //もし全データに変更がなかったらend_flag=1
                int n_e=0;
                for(b=0;b<16;b++){
                    if(o1[b] == set1[b] && o2[b]== set2[b]){
                        n_e += 1;
                    }
                }
                if(n_e == 0){
                    end_flag=1;
                }
                ////////////////////////////////////////
            }//26データ全てを調べる
        }//値が変動しなかったらループを終了
        
        //各ノードの個数を調べる
        for(a=0;a<16;a++){
            if(o1[a] > o2[a]){
                node1+=1;
            } else {
                node2+=1;
            }
        }
    }//ノード数が等しければ終了
    
    //中心値を表示
    printf("end\n");
    printf("o1:\n");
    for(a=0;a<16;a++){
        printf(" %.3f,",o1[a]);
    }
    printf("\n");
    printf("o2:\n");
    for(a=0;a<16;a++){
        printf(" %.3f,",o2[a]);
    }
    printf("\n");
    printf("\n");
    
    ////////////////////////////
    printf("class1:\n");
    for(a=0;a<16;a++){
        if(o1[a] > o2[a]){
            printf("%d,",a);
        }
    }
    printf("\n");
    printf("class2:\n");
    for(a=0;a<16;a++){
        if(o2[a] > o1[a]){
            printf("%d,",a);
        }
    }
    ///////////////////////////
    printf("\n");
}