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
#include "shortestPath.h"
#include "dynamicProgramming.h"


/**
 * 排序类型
 */
typedef enum {
    
    SortTypeBucket, // 桶排序
    SortTypeBubble, // 冒泡排序
    SortTypeQuick, // 快速排序
    SortTypeMaxHeap,  // 最大堆排序, 结果是从小到大排序
    SortTypeMinHeapTopK,  //  利用堆特性, 找出前 K 大的数
    SortTypeMerge   // 归并排序
    
}SortType;

/**
 * 搜索类型
 */
typedef enum {
    
    SearchTypeDepthFirst, // 深度优先
    SearchTypeBreadthFirst  // 广度优先
    
}SearchType;

/**
 * 最短路径搜索类型
 */
typedef enum {
    
    ShortestPathSearchTypeFloyd, // Floyd-Warshall算法
    ShortestPathSearchTypeDijkstra  // Dijkstra算法
    
}ShortestPathSearchType;


/**
 * 动态规划法具体处理的问题类型
 */
typedef enum {
    
    DPproblemTypeKnapsackProblem, // 动态规划法解 0-1背包问题
    DPproblemTypeLevenshteinDistance // 字符串编辑距离
    
}DPproblemType;


#pragma mark - 排序
/**
 *  排序算法
 */
void sortGo(SortType sortType){
    
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
            
        case SortTypeMinHeapTopK:
            // 5> 利用最小堆特性, 找出前 K 大的数
            {
                int topK = 6;
                heapSortTopK(array,arrayLength ,topK);

                break;
                
            }
            
        case SortTypeMerge:
            // 6> 归并排序  时间复杂度: O( N*Log(N) )
            mergeSort(array, arrayLength);
            
            break;
            
        default:
            break;
    }
    
}


#pragma mark - 深度/广度--优先搜索

/**
 *  搜索算法 , 深度优先搜索/广度优先搜索
 */
void searchGo( SearchType searchType){
    
    switch (searchType) {
        case SearchTypeDepthFirst: // >深度优先搜索   >> 输出 n 的全排列
            {
                printf("******* 深度优先搜索 **************\n");
                int n = 3;
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


#pragma mark - 最短路径问题

void shortestPathGo(ShortestPathSearchType shortestPathSearchType){
    
    
    switch (shortestPathSearchType) {
        case ShortestPathSearchTypeFloyd: // FloydWarshall算法求任意两点间最短路径
            {
                
                printf("*******FloydWarshall算法求任意两点间最短路径**************\n");
                int map[4][4] = { // map[i][j] = s  表示: i,j 两点间的距离是 s,  inf 表示 i,j 两点走不通
                    {0,2,6,4},
                    {inf,0,3,inf},
                    {7,inf,0,1},
                    {5,inf,12,0}
                };
                
                printf("各点间距离图: 999999 表示两点走不通\n");
                for (int i=0; i<4; i++) {
                    for (int j=0; j<4; j++) {
                        
                        printf("%8d ",map[i][j]);
                        
                    }
                    printf("\n");
                }
                
                // FloydWarshall算法
                floydWarshallSearch(map,4);
                
                
                break;
            }
            
        case ShortestPathSearchTypeDijkstra:  // Dijkstra算法求给定源点到其他各点的最短距离
            {
                printf("*******Dijkstra算法求给定源点到其他各点的最短距离*****************\n");
                int map[6][6] = { // map[i][j] = s  表示: i,j 两点间的距离是 s,  inf 表示 i,j 两点走不通
                    {0,1,12,inf,inf,inf},
                    {inf,0,9,3,inf,inf},
                    {inf,inf,0,inf,5,inf},
                    {inf,inf,4,0,13,15},
                    {inf,inf,inf,inf,0,4},
                    {inf,inf,inf,inf,inf,0}
                };
                
                printf("各点间距离图: 999999 表示两点走不通\n");
                for (int i=0; i<6; i++) {
                    for (int j=0; j<6; j++) {
                        
                        printf("%8d ",map[i][j]);
                        
                    }
                    printf("\n");
                }
                
                int pointCount = 6;
                int sourcePoint = 1; // 取值: 0 ~ pointCount-1
                
                dijkstraSearch(map,sourcePoint,pointCount);
                
                
                break;
            }
            
            
        default:
            break;
    }
    
}

#pragma mark - 动态规划法

void dynamicProgrammingGo( DPproblemType dpProblemType){
    
    switch (dpProblemType) {
            
        case DPproblemTypeKnapsackProblem: // 0-1 背包问题
            {
                int valueArr[7]={10,40,30,50,35,40,30};      // 物品权重(价值)
                int weightArr[7]={35,30,60,50,40,10,25};      // 物品大小
                int MaxWeight = 150;  // 背包所能承受的最大重量
                
//                int weightArr[5]={2,2,6,5,4};      // 物品权重(价值)
//                int valueArr[5]={6,3,5,4,6};      // 物品大小
//                int MaxWeight = 10;  // 背包所能承受的最大重量
                
                
                // 获取物品个数
                int count = sizeof(weightArr)/sizeof(weightArr[0]);
               
                // 动态规划法求解 0-1 背包问题
                knapsackProblemWithDP(weightArr, valueArr, count, MaxWeight);
                
                
                /**** 补充: 回溯法解 0-1背包问题 **/
                knapsackProblemWithBacktracking(weightArr, valueArr, count, MaxWeight);
                
                
                break;
            }
            
        case DPproblemTypeLevenshteinDistance:  // 两个字符串间的最小编辑距离问题, Levenshtein Distance
            {
                char *srcStr = "abc";
                char *targetStr = "dBkl";
                
                // *** 单纯的递归法
                levenshteinDistanceWithPureRecursion(srcStr, targetStr);
                
                // *** 优化后的递归, 排除重复的计算
                levenshteinDistanceWithOptimizeRecursion(srcStr, targetStr);
                
                
                
                
                break;
            }
            
            
        default:
            break;
    }
    
}



#pragma mark - 主函数
int main() {
    
// 排序算法测试
    // 全排序
    sortGo(SortTypeMaxHeap);
    // 最小堆处理 Top K问题
    sortGo(SortTypeMinHeapTopK);
    
// 搜索算法测试
    searchGo(SearchTypeDepthFirst);
    searchGo(SearchTypeBreadthFirst);
    
// 最短路径问题
    shortestPathGo(ShortestPathSearchTypeDijkstra);
    
// 动态规划法应用
    // 求解 0-1背包问题
    dynamicProgrammingGo(DPproblemTypeKnapsackProblem);
    // 字符串编辑距离 Levenshtein Distance
    dynamicProgrammingGo(DPproblemTypeLevenshteinDistance);
    
    
    return 0;
    
}
