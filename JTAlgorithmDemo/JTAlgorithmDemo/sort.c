//
//  sort.c
//  JTAlgorithmDemo
//
//  Created by BJT on 17/8/14.
//  Copyright © 2017年 BJT. All rights reserved.
//

#include "sort.h"

#include <string.h>
#include <stdlib.h>

/********* 桶排序 *******/

void displaySortedArray(int sorted[],int length);

void bucketSort(int a[],int length, int max){
    
    printf("***********桶排序**************\n");
    
    // 排序前
    printf("排序前\n");
    for (int i = 0; i < length; i++) {
         printf("%d ",a[i]);
    }
    printf("\n");
    
    // 创建一个桶数组
    int *bucket;
    if ((bucket = (int *)malloc(sizeof(int)*max))== NULL) return;
    memset(bucket,0,max * sizeof(int));
    
    for (int i = 0; i < length; i++) {
        // 相应值放入相应的桶
        bucket[a[i]]++;
        
    }
    // 输出排序后的结果
    displaySortedArray(bucket, max);
    
    free(bucket); // 释放内存
}



void displaySortedArray(int sorted[],int length){
    
    
    printf("排序后\n");
    for (int i = 0; i < length; i++) {
        
        for( int j = 0; j < sorted[i]; j++ ){
            
            printf("%d ",i);
            
        }
    }
    printf("\n");
    
    printf("******************************\n");
}
/*****************************************/



/**********冒泡排序*********************/


void bubbleSort(int a[], int length){
    
    printf("***********冒泡排序**************\n");
    
    // >排序前输出
    printf("排序前\n");
    for (int i = 0; i < length; i++) {
        printf("%d ",a[i]);
    }
    printf("\n");
    
    // >排序
//    int temp = 0;
    for (int i = 0; i < length-1; i++) {
        
        for (int j = 0; j < length -1 - i; j++) {
            
            if (a[j] > a[j+1]) { // 从小到大
                // 异或交换两个数
                a[j] = a[j]^a[j+1];
                a[j+1] = a[j]^a[j+1];
                a[j] = a[j]^a[j+1];
                
//                temp = a[j];
//                a[j] = a[j+1];
//                a[j+1] = temp;
                
            }
        }
        
        
    }
    
    // >排序后输出
    printf("排序后\n");
    for (int i = 0; i < length; i++) {
        printf("%d ",a[i]);
    }
    printf("\n");
    printf("******************************\n");
}


/*****************************************/


/**********快速排序*********************/


/**
 *  递归快速排序
 */
void qSort(int a[],int left, int right){
    
    if (left > right) // 递归的退出条件
        return;
        
    // 选最左侧为基准数
    int base = a[left];
    int i = left;
    int j = right;
    
    while (i != j) {
        
        // 注意下面两个 while 循环的顺序, right 必须在前面
        while(a[j] >= base && i < j){ // 从最右侧开始成查找比基准数小的数
            
            j--;
        }
        while (a[i] <= base && i < j ) { // 从左侧开始成查找比基准数大的数
            
            i++;
        }
        
        if (i < j) {
            
            // 异或交换两个数
            a[i] = a[i]^a[j];
            a[j] = a[i]^a[j];
            a[i] = a[i]^a[j];
            
        }
    }
    
    // i,j 相遇 , 基准数归位
    a[left] = a[i];
    a[i] = base;
    
    qSort(a, left, i-1); // 基准数左侧再进行快速排序
    qSort(a, i+1, right); // 基准数右侧再进行快速排序
    
    
}

void quickSort(int a[], int length){
    
    printf("***********快速排序**************\n");
    
    // >排序前
    printf("排序前\n");
    for (int i = 0; i < length; i++) {
        printf("%d ",a[i]);
    }
    printf("\n");
    
    // >快速排序函数
    qSort(a,0,length-1);
    
    
    // >排序后输出
    printf("排序后\n");
    for (int i = 0; i < length; i++) {
        printf("%d ",a[i]);
    }
    printf("\n");
    printf("******************************\n");
    
}



/*****************************************/
