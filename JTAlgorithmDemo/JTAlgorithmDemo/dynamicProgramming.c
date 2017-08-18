//
//  dynamicProgramming.c
//  JTAlgorithmDemo
//
//  Created by BJT on 17/8/18.
//  Copyright © 2017年 BJT. All rights reserved.
//

#include "dynamicProgramming.h"
#include <stdlib.h>
#include <string.h>
#include "common.h"

/**********0-1背包问题***********************************/

#pragma mark - 0/1 背包问题

/**
 *  动态规划法处理背包问题
*/

void knapsackProblemWithDP(int *weightArr,int *valueArr,int count, int MaxWeight){
    
    // 输出初始信息
    printf("************* 动态规划法处理 0/1 背包问题****************\n");
    
    printf("物品编号: ");
    for (int i=0; i<count; i++) {
        
        printf("%3d ",i+1);
    }
    printf("\n");
    
    printf("物品重量: ");
    for (int i=0; i<count; i++) {
        
        printf("%3d ",weightArr[i]);
    }
    printf("\n");
    printf("物品价值: ");
    for (int i=0; i<count; i++) {
        
        printf("%3d ", valueArr[i]);
    }
    printf("\n");
    
    // 求最优解
    int row = count + 1;  // 行: 0 1 2 ... count
    int col = MaxWeight + 1; // 列: 0 1 2 3 ...MaxWeight
    
    int maxValueArr[row][col]; // 二维数组 maxValueArr[i][j], 表示  背包最大容量为 j 时,前 i 个物品进行放入所能取得的最大价值
    
    int maxValue_i_1_j;
    int maxValue_i_j;
    
    for (int i=0; i<row; i++) {
        
        for(int j=0; j<col; j++){
            
            if ( i==0 || j==0) { // 第一行,或第一列 置为 0
                
                maxValueArr[i][j] = 0;
                
            }else if(weightArr[i-1] > j){  // 第 i 个物品重量大于背包承重, 即装不下 i
               
                maxValueArr[i][j] = maxValueArr[i-1][j];
                
            }else{
                
                maxValue_i_1_j = maxValueArr[i-1][j]; // 不放 i
                maxValue_i_j = maxValueArr[i-1][j-weightArr[i-1]] + valueArr[i-1]; //  放 i
                
                maxValueArr[i][j] = max_int( maxValue_i_1_j , maxValue_i_j);
                
            }
            
            
            
        }
        
    }
    
    
    // 输出计算结果
    int optValue = maxValueArr[count][MaxWeight];
    
    if ( optValue ) {
        
        printf("找到最优解,总价值: %d\n被装进背包的物品如下:\n" , optValue);
        
        int i = count , j = MaxWeight;
        int maxValue_i_j;
        
        while (i>0) { // 查找被选中的物品
            
            maxValue_i_j = maxValueArr[i-1][j-weightArr[i-1]] + valueArr[i-1];
            if (maxValueArr[i][j] == maxValue_i_j) { // i 被选中
                
                printf("编号: %d  重量: %d  价值: %d\n",i, weightArr[i-1], valueArr[i-1]);
                j -= weightArr[i-1];
                
            }
            
            i--;
        }
        
    } else{
        
        printf("❌--未找到最优解\n");
    }
    
    printf("********************************************\n");
    
}


/*****************************************************/