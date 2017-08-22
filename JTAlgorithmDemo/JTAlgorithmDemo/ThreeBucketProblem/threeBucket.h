//
//  threeBucket.h
//  JTAlgorithmDemo
//
//  Created by BJT on 17/8/21.
//  Copyright © 2017年 BJT. All rights reserved.
//

/*
 *   there are an 8-liter bucket filled with water and empty 3-liter and 5-liter buckets. 
 *   find solution to divide the 8 liters of water into two equal parts of 4 liters
 *
 */


#ifndef threeBucket_h
#define threeBucket_h

#include <stdio.h>

typedef int* BucketState; // BucketState[3] 三个水桶的水量状态

/**
 *  深度搜索解决三个水桶等分水问题
 *
 *  @param bucketStartState 水桶初始状态,各个水桶水量
 *  @param bucketEndState   目标状态
 *  @param bucketCapacity   三个水桶容量
 */
void threeBucketProblemWithDfs(BucketState bucketStartState, BucketState bucketEndState, int *bucketCapacity);


#endif /* threeBucket_h */
