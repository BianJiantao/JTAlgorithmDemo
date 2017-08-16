//
//  shortestPath.h
//  JTAlgorithmDemo
//
//  Created by BJT on 17/8/15.
//  Copyright © 2017年 BJT. All rights reserved.
//  最短路径问题求解算法 

#ifndef shortestPath_h
#define shortestPath_h

#include <stdio.h>

#define inf 999999  // 表示两点距离无穷大, 路走不通


/**
 *  FloydWarshall算法求任意两点最短路径
 *
 *  @param map        两点间的距离矩阵
 *  @param pointCount 点的个数
 */
void floydWarshallSearch(int map[][4],int pointCount);


void dijkstraSearch(int map[][6],int sourcePoint,int pointCount);



#endif /* shortestPath_h */
