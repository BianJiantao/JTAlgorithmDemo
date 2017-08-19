//
//  dynamicProgramming.h
//  JTAlgorithmDemo
//
//  Created by BJT on 17/8/18.
//  Copyright © 2017年 BJT. All rights reserved.
//  动态规划算法--应用

#ifndef dynamicProgramming_h
#define dynamicProgramming_h

#include <stdio.h>



/*** Knapsack problem(0-1背包问题) */
#pragma  mark - Knapsack problem(0-1背包问题)

/**
 *  动态规划法解 0-1背包问题
 *
 *  @param weightArr 物品重量数组
 *  @param valueArr  物品价值数组
 *  @param count     物品个数
 *  @param MaxWeight 背包最大承重
 */
void knapsackProblemWithDP(int *weightArr,int *valueArr,int count, int MaxWeight);

/**
 *  回溯法解 0-1背包问题
 *
 *  @param weightArr 物品重量数组
 *  @param valueArr  物品价值数组
 *  @param count     物品个数
 *  @param MaxWeight 背包最大承重
 */
void knapsackProblemWithBacktracking(int *weightArr,int *valueArr,int count, int MaxWeight);





#endif /* dynamicProgramming_h */
