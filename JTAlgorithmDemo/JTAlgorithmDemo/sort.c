//
//  sort.c
//  JTAlgorithmDemo
//
//  Created by BJT on 17/8/14.
//  Copyright © 2017年 BJT. All rights reserved.
//


#include <string.h>
#include <stdlib.h>


#include "sort.h"


/********* 桶排序 *********************/

#pragma mark - 桶排序
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


#pragma mark - 冒泡排序

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

#pragma mark - 快速排序

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

/**********最大堆排序*********************/

#pragma mark - 最大堆排序

/**
 *  对非叶结点 i 向下调整,使其符合最大堆特性
 *
 *  @param a 二叉树
 *  @param i 待调整节点编号
 */
void shiftDown(int heap[],int i,int length){
    
    BOOL flag = FALSE; // 标记是否已是最大堆
    while( (i*2 <= length-1) && flag == FALSE ){ // 当前节点有左子节点,且需要向下调整
        
        int max ; // 当前节点及其子节点中最大的节点编号
        if (heap[i] < heap[i*2]) { // 当前节点小于左子节点
          
            max = 2*i;
            
        }else{
            
            max = i;
        }
        
        if ( (i*2+1) <= length-1 ) { // 当前节点有右子节点
            
            if (heap[max] < heap[i*2+1]) { // 右子节点更大
                
                max = i * 2 + 1;
            }
            
        }
        
        if (max != i ) { // 最大的节点不是自己,进行交换
            
            // 异或交换两个数
            heap[i] = heap[i]^heap[max];
            heap[max] = heap[i]^heap[max];
            heap[i] = heap[i]^heap[max];
            
            i = max; // 继续向下调整
        } else{
            
            flag = TRUE; // 已是最大堆
        }
    
    
    
    }
    
}


/** 创建最大堆 */
void creatMaxHeap(int heap[],int length){
    
    for (int i = length * 0.5 - 1; i >= 0; i--) { // 二叉树的非叶节点
        
        shiftDown(heap,i,length);
        
        
    }
    
}

/** 排序 */
void hSort(int heap[],int length){
    
    
    while (length > 1) {
        
        // 堆的首尾交换
        int end = length -1 ;
        heap[0] = heap[0]^heap[end];
        heap[end] = heap[0]^heap[end];
        heap[0] = heap[0]^heap[end];
        
        // 堆尾已是最大值,排除,对剩余部分继续排序
        length--;
        
        // 堆首向下调整,使其满足最大堆特性
        shiftDown(heap, 0, length);
        
    }
    
    
}

void  maxHeapSort(int heap[],int length){
    
    printf("***********最大堆排序**************\n");
    // >排序前
    printf("排序前\n");
    for (int i = 0; i < length; i++) {
        printf("%d ", heap[i]);
    }
    printf("\n");
    
    
    // >创造最大堆
    creatMaxHeap(heap, length);
    
    // >从小到大排序
    hSort(heap,length);
    
    
    // >排序后输出
    printf("排序后\n");
    for (int i = 0; i < length; i++) {
        printf("%d ",heap[i]);
    }
    printf("\n");
    printf("******************************\n");
}


/*****************************************/

