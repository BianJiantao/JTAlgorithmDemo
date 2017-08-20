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
#pragma mark 动态规划法
/**
 *  动态规划法解 0-1背包问题
 *
 *  @param weightArr 物品重量数组
 *  @param valueArr  物品价值数组
 *  @param count     物品个数
 *  @param MaxWeight 背包最大承重
 */
void knapsackProblemWithDP(int *weightArr,int *valueArr,int count, int MaxWeight);

#pragma mark 回溯法
/**
 *  回溯法解 0-1背包问题
 *
 *  @param weightArr 物品重量数组
 *  @param valueArr  物品价值数组
 *  @param count     物品个数
 *  @param MaxWeight 背包最大承重
 */
void knapsackProblemWithBacktracking(int *weightArr,int *valueArr,int count, int MaxWeight);



/*** 字符串编辑距离 Levenshtein distance */
#pragma  mark - 字符串编辑距离  Levenshtein distance

#pragma mark 单纯递归法
/**
 *  单纯递归法计算 字符串最小编辑距离
 *
 *  @param sourceString 源字符串
 *  @param targetString 目标字符串
 *
 *  @return 二者最小编辑距离
 */
int levenshteinDistanceWithPureRecursion(char *sourceString,char *targetString);

#pragma mark 优化递归法
/**
 * 单纯递归法, 对同一个字符串状态会有重复计算,
 * 可以利用动态规划思想对其优化,记录每一个状态,
 * 如果是相同状态且计算过,直接返回,否则再进行计算
 */


/**
 *  优化递归法计算 字符串最小编辑距离
 *
 *  @param sourceString 源字符串
 *  @param targetString 目标字符串
 *
 *  @return 二者最小编辑距离
 */
int levenshteinDistanceWithOptimizeRecursion(char *sourceString,char *targetString);


#pragma mark 动态规划法




#endif /* dynamicProgramming_h */
