//
//  main.c
//  JTAlgorithmDemo
//
//  Created by BJT on 17/8/14.
//  Copyright © 2017年 BJT. All rights reserved.
//

#include <stdio.h>

#include "sort.h"
#include "search.h"


/**
 * 排序类型
 */
typedef enum {
    
    SortTypeBucket, // 桶排序
    SortTypeBubble, // 冒泡排序
    SortTypeQuick, // 快速排序
    SortTypeMaxHeap  // 最大堆排序, 结果是从小到大排序
    
}SortType;

/**
 * 搜索类型
 */
typedef enum {
    
    SearchTypeDepthFirst, // 深度优先
    SearchTypeBreadthFirst  // 广度优先
    
}SearchType;



/**
 *  排序算法
 */
void sortGo(SortType sortType){
    
    /************排序算法******************************************/
    
    // 待排序数列
    int array[] = {1,53,5,9,4,45,21,7,3,4,0};
    // 数列最大值.作为最大的桶
    int maxValue = 100;
    // 获取数组长度
    int arrayLength = sizeof(array)/sizeof(array[0]);
    
    switch (sortType) {
        case SortTypeBucket:
            // 1> 桶排序  时间复杂度: O( N+M )
                bucketSort(array, arrayLength, maxValue+1);
            break;
            
        case SortTypeBubble:
            // 2> 冒泡排序  时间复杂度: O( N^2 )
                bubbleSort(array, arrayLength);
            break;
            
        case SortTypeQuick:
            // 3> 快速排序  时间复杂度: O( N*Log(N) )
            quickSort(array, arrayLength);
            break;
            
        case SortTypeMaxHeap:
            // 4> 最大堆排序  时间复杂度: O( N*Log(N) )
            maxHeapSort(array, arrayLength);
            break;
            
            
        default:
            break;
    }
    
    /******************************************************/
    
    
}

/**
 *  搜索算法 , 深度优先搜索/广度优先搜索
 */
void searchGo( SearchType searchType){
    
    switch (searchType) {
        case SearchTypeDepthFirst: // >深度优先搜索   >> 输出 n 的全排列
            {
                printf("******* 深度优先搜索 **************\n");
                int n = 4;
                depthFirstSearch(n);
                
                break;
            }
            
        case SearchTypeBreadthFirst: // >广度优先搜索  >> 搜索地图中两点间最短路径
        {
            int map[5][4] = { // 地图, 坐标 1 表示障碍物,不能通行; 0 表示可以通过
                {0,0,1,0},
                {0,0,0,0},
                {0,0,1,0},
                {0,1,0,0},
                {0,0,0,1}
            };
            
            Point start = {0,0}; // 起点
            Point target = {3,2}; // 目标点
            
            printf("******* 广度优先搜索--搜索地图两给定点最短路径 **************\n");
            printf("给定地图, 1 表示障碍物, 0 表示可以通行\n");
            for (int i=0; i<5; i++) {
                for (int j=0; j<4; j++) {
                    
                    printf("%d ",map[i][j]);
                    
                }
                printf("\n");
            }
            printf("起点:(%d,%d)---目标点:(%d,%d)\n",start.x,start.y,target.x,target.y);
            
            breadthFirstSearch(map,5,4,start,target);
        }
            break;
            
        default:
            break;
    }
    
}


int main() {
    
    // 排序算法测试
    sortGo(SortTypeMaxHeap);
    
    // 搜索算法测试
    searchGo(SearchTypeBreadthFirst);
    
    
    return 0;
    
}
