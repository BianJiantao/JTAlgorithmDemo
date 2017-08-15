//
//  search.c
//  JTAlgorithmDemo
//
//  Created by BJT on 17/8/15.
//  Copyright © 2017年 BJT. All rights reserved.
//

#include "search.h"

#include "common.h"


/********* 深度优先搜索 *********************/

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
    printf("******* 深度优先搜索 **************\n");
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


void breadthFirstSearch(){
    
    
    
}




/**********************************************/
