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



void depthFirstSearch(int n);

void breadthFirstSearch(int map[][4],int row,int col,Point start,Point target);


#endif /* search_h */

