//
//  common.h
//  JTAlgorithmDemo
//
//  Created by BJT on 17/8/15.
//  Copyright © 2017年 BJT. All rights reserved.
//  公用的代码处理

#ifndef common_h
#define common_h

#include <string.h>
#include <stdlib.h>

#define  FALSE 0
#define TRUE 1
#define BOOL int

/**
 *  坐标点
 */
typedef struct {
    int x;
    int y;
    
}Point;

/**
 *  获取两个 int 型整数最大值
 */
int max_int(int a,int b);

/**
 *  获取两个 int 型整数最小值
 */
int min_int(int a,int b);

#endif /* common_h */
