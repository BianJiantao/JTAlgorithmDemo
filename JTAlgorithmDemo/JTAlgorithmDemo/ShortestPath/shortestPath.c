//
//  shortestPath.c
//  JTAlgorithmDemo
//
//  Created by BJT on 17/8/15.
//  Copyright © 2017年 BJT. All rights reserved.
//

#include "shortestPath.h"
#include "common.h"

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


/********* Dijkstra算法求给定源点到其他各点的最短距离 *********************/
#pragma mark - Dijkstra算法

void dijkstraSearch(int map[][6],int sourcePoint, int pointCount){
    
    if( sourcePoint >= pointCount )
        return;
    // 源点到各点的距离数组
    int dis[pointCount];
    // 用于标记已计算出最短路径的点
    BOOL book[pointCount];
    
    // 初始化
    for (int i = 0; i<pointCount; i++) {
        dis[i] = map[sourcePoint][i];
        book[i] = FALSE;
    }
    
    book[sourcePoint] = TRUE;
    
    // Dijkstra算法
    int min; // 最小距离
    int minPoint = 0; // 距源点最近的点
    for(int i = 0; i<pointCount - 1; i++){
        
        min = inf;
        for (int j = 0; j < pointCount; j++) { // 从未标记的点中找出离源点最近的点
            
            if(book[j] == FALSE && dis[j] < min){
                
                min = dis[j];
                minPoint = j;
                
            }
        
        }
        
        book[minPoint] = TRUE;  // 标记最近的点
        
        // 以该最近点为中转点继续搜索
        for(int k = 0; k<pointCount; k++ ){
            
            
            if (map[minPoint][k] >= inf)  // 两点间走不通,继续下一点
                continue;
            // 走得通
            if( dis[k] > dis[minPoint]+map[minPoint][k] ){ // 通过 minPoint 点可以缩短源点到 k 点的距离, 更新 dis[k]
                
                dis[k] = dis[minPoint]+map[minPoint][k];
                
            }

            
        }
        
    }
    
    // 输出结果
    printf("源点 %d 到各点间最短距离: 🚫表示两点间走不通\n",sourcePoint);
    for (int i=0; i<pointCount; i++) {
        dis[i] == inf ? printf("🚫"):printf("%8d ",dis[i]); //  🚫表示两点间走不通
    }
    
    printf("\n");
    
    printf("********************************************\n");
    
    
}


/**********************************************/

