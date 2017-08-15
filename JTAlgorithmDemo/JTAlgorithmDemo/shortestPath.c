//
//  shortestPath.c
//  JTAlgorithmDemo
//
//  Created by BJT on 17/8/15.
//  Copyright © 2017年 BJT. All rights reserved.
//

#include "shortestPath.h"

/********* FloydWarshall算法求任意两点最短路径 *********************/
#pragma mark - FloydWarshall算法
/**
 *  FloydWarshall算法求任意两点最短路径
 *
 *  @param map        两点间的距离矩阵
 *  @param pointCount 点的个数
 */
void floydWarshallSearch(int map[][4],int pointCount){

    for(int k=0; k<pointCount; k++ ){ // 经过 0~k 点进行中转, 判断能否缩短 i, j 两点间距离
        
        for (int i=0; i<pointCount; i++) {
            
            for (int j=0; j<pointCount; j++) {
                
                if(map[i][k] == inf || map[k][j] == inf)
                    continue;
                if( map[i][j] > map[i][k] + map[k][j] ){ // 中转点可以缩短 i,j 两点间距离, 更新该距离值
                    map[i][j] = map[i][k] + map[k][j];
                }
                
                
            }
            
        }
        
    }
    
    printf("各点间最短距离:\n");
    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            
            printf("%8d ",map[i][j]);
            
        }
        printf("\n");
    }
    
    printf("\n********************************************\n");
}


/**********************************************/