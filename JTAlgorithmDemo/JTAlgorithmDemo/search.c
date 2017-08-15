//
//  search.c
//  JTAlgorithmDemo
//
//  Created by BJT on 17/8/15.
//  Copyright © 2017年 BJT. All rights reserved.
//


#include <stdlib.h>
#include <string.h>

#include "search.h"


/********* 深度优先搜索 *********************/
#pragma mark - 深度优先搜索
/**
 *  深度优先搜索算法实现
 *
 *  @param n    待求全排列的数值
 *  @param a    存储一种全排列
 *  @param book 标记 i 是否已参与排列
 *  @param step 当前排列到第几步 (总共 n 步)
 */
void dfs(int n, int a[], int book[], int step){
    
    static int count = 0;
    
    if (step == n+1) { // 搜索到第 n+1 步,说明已找到一种排列
        
//        count++;
        printf("第 %d 种排列:  ",++count);
        for(int i =1; i<n+1; i++){
            
            printf("%d ",a[i]);
        }
        
        printf("\n");
        
        return;
    }
    
    for (int i=1; i<n+1; i++) {
        
        if (book[i] == FALSE) { // i 还没有参与排列
            
            a[step] = i; // 第 step 步使用 i 排列
            book[i] = TRUE; // i 已参与排列
            
            dfs(n, a, book, step+1); // 搜索下一步
            book[i] = FALSE; // 使用 i 搜索完毕,置为 false,  便于后续step搜索使用 i
        }
        
    }
    
    return;
}


void depthFirstSearch(int n){
    printf("以下为 %d 的全排列\n",n);
    
    int a[n];  // 存储每一种排列
    BOOL book[n];  // 标记 i 是否已参与排列
    // 初始化
    for (int i=0; i<n+1; i++) {
        a[i] = 0;
        book[i] = FALSE;
    }
    
    // >深度优先搜索
    dfs(n, a, book, 1);
    
    
    printf("******************************\n");
    
}

/**********************************************/

/********* 广度优先搜索 *********************/
#pragma mark - 广度优先搜索

typedef struct {
    
    Point point; // 地图中某一点
    int preNodeNumber; // 上一个坐标点在队列的编号
    int steps; // 从起点到当前点的步数
    
}PathNode;

/**
 *  从当前坐标点利用 preNodeNumber 进行回溯,直到找到起点, 并输出回溯点坐标
 */
void displayPath(PathNode queue[],int curr){

    if (curr == 0) { // 回到起点
        
        printf("(%d,%d)",queue[curr].point.x,queue[curr].point.y);
        return;
    }
    
    // 回溯
    int pre = queue[curr].preNodeNumber;
    displayPath(queue, pre);
    
    printf("->(%d,%d)",queue[curr].point.x,queue[curr].point.y);
    
    
}

/**
 * 广度优先搜索
 */
void breadthFirstSearch(int map[][4],int row,int col,Point start,Point target){
    
    
    if (  (start.x == target.x) && (start.y == target.y) ) //  起始点就是目标点
        return;
    
    // >准备工作
     BOOL *book[row]; // 标记某一坐标点是否在路径中
    for (int i =0 ; i<row; i++) {
        
        if ((book[i] = (int *)malloc(sizeof(int)*col))== NULL) return;
        memset(book[i],FALSE,col * sizeof(int));
    }
    
    int nextVector[4][2] = { // 方向矢量, 顺时针
        {0,1}, // 向右走
        {1,0}, // 向下走
        {0,-1}, // 向左走
        {-1,0}, // 向上走
    };
    
    PathNode queue[row*col]; // 队列
    int head,tail; // 队列的首尾
    BOOL flag; // 是否到达目标点的标记
    int nextPointX,nextPointY;
    
    // >初始化
    head = tail = 0;
    flag = FALSE;
    // 起始点入列
    queue[tail].point = start;
    queue[tail].preNodeNumber = 0;
    queue[tail].steps = 0;
    tail++;
    // 标记入列的点
    book[start.x][start.y] = TRUE;
    
    
    while(head < tail){  // 队列不为空
        
        // 沿着方向矢量进行扩展
        for(int i=0; i<4; i++){
            
            // 下一点的坐标
            nextPointX = queue[head].point.x + nextVector[i][0];
            nextPointY = queue[head].point.y + nextVector[i][1];
            // 判断下一点是否超出地图范围
            if(nextPointX < 0 || nextPointX >= row || nextPointY < 0 || nextPointY >= col) // 该方向扩展越界
                continue; // 计算下一个方向
            
            if(map[nextPointX][nextPointY] != 0 || book[nextPointX][nextPointY] != 0) // 下一点是障碍物或者已在搜索路径, 继续搜索下一个方向
                continue;
            
            // // 来到这里,说明 nextPoint 可以继续走
            // 入列
            queue[tail].point.x = nextPointX;
            queue[tail].point.y = nextPointY;
            queue[tail].preNodeNumber = head; //
            queue[tail].steps = queue[head].steps + 1; // 步数 + 1
            tail++;
            // 标记该点到路径中
            book[nextPointX][nextPointY] = TRUE;
            
            if(nextPointX == target.x && nextPointY == target.y){ // 是目标点
                
                flag = TRUE; // 标记找到目标
                break; // 跳出 for 循环
                
            }
            
        }
        
        if(flag == TRUE)  // 找到目标点
            break;
        head++ ; // 队首的坐标点搜索完毕,出列; 以便下一点继续搜索
        
    }
    
    printf("搜索结果:\n");
    if (flag == TRUE) {
        
        printf("最短路径步数: %d\n最短路径: \n",queue[tail-1].steps);
        
        // 输出最短路径
        displayPath(queue,tail-1);
        
    }else
        printf("该目标点不能到达");
    
    printf("\n********************************************\n");
    
    
}


/**********************************************/
