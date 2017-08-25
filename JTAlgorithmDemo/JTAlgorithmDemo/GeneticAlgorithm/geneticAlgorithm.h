//
//  geneticAlgorithm.h
//  JTAlgorithmDemo
//
//  Created by BJT on 17/8/24.
//  Copyright © 2017年 BJT. All rights reserved.
//  遗传算法

#ifndef geneticAlgorithm_h
#define geneticAlgorithm_h

#include <stdio.h>

#pragma  mark - 遗传算法解 0-1背包问题
/**
 *  遗传算法解 0-1背包问题
 *
 *  @param weightArr 物品重量数组
 *  @param valueArr  物品价值数组
 *  @param count     物品个数
 *  @param MaxWeight 背包最大承重
 */
void knapsackProblemWithGA(int *weightArr,int *valueArr,int count, int MaxWeight);



#endif /* geneticAlgorithm_h */
