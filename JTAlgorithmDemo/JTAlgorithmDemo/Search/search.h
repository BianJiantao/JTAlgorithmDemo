//
//  search.h
//  JTAlgorithmDemo
//
//  Created by BJT on 17/8/15.
//  Copyright © 2017年 BJT. All rights reserved.
// 深度优先搜索 - dfs,  广度优先搜索 - bfs

#ifndef search_h
#define search_h

#include <stdio.h>


#include "common.h"


/**
 *  深度优先搜索   
 *
 *  @param n 输出 n 的全排列
 */
void depthFirstSearch(int n);
/**
 *  广度优先搜索  ---搜索地图中两点间最短路径
 *
 *  @param map    地图矩阵
 *  @param row    行数
 *  @param col    列数
 *  @param start  起点
 *  @param target 目标点
 */
void breadthFirstSearch(int map[][4],int row,int col,Point start,Point target);


#endif /* search_h */

