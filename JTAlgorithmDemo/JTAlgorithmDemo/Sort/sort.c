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

/* TIPS: 优化的途径
 * 1. 最简单的改进方法是加入一标志性变量exchange，用于标志某一趟排序过程中是否有数据交换，如果进行某一趟排序后并没有进行数据交换，则说明数据已经按要求排列好，可立即结束排序，避免不必要的比较过程
 * 2. 设置一个pos指针，pos后面的数据在上一轮排序中没有发生交换，下一轮排序时，就对pos之后的数据不再比较。
 * 3. 可以在每次循环之中进行正反两次冒泡，分别找到最大值和最小值，下轮循环直接去掉两头,如此可使排序的轮数减少一半。
 */

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
    BOOL isSorted = TRUE; // 传入的数据是否已是有序的,默认 是
    for (int i = 0; i < length-1; i++) {
        isSorted = TRUE;
        for (int j = 0; j < length -1 - i; j++) {
            
            if (a[j] > a[j+1]) { // 从小到大
                // 异或交换两个数
                a[j] = a[j]^a[j+1];
                a[j+1] = a[j]^a[j+1];
                a[j] = a[j]^a[j+1];
                
//                temp = a[j];
//                a[j] = a[j+1];
//                a[j+1] = temp;
                
                isSorted = FALSE; // 发生了交换,是无序
            }
        }
        
        if (isSorted) { // 上一轮比较, 数据是未发生交换,已是有序的,直接返回   最好的排序情况, 第一轮就是有序的,复杂度 O(N)
            
            printf("数据已是有序的\n");
            printf("******************************\n");
            return;
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
void shiftDownToMaxHeap(int heap[],int i,int length){
    
    BOOL flag = FALSE; // 标记是否已是最大堆
    while( (i*2+1 <= length-1) && flag == FALSE ){ // 当前节点有左子节点,且需要向下调整
        
        int max ; // 当前节点及其子节点中最大的节点编号
        if (heap[i] < heap[i*2+1]) { // 当前节点小于左子节点
          
            max = 2*i+1;
            
        }else{
            
            max = i;
        }
        
        if ( (i*2+2) <= length-1 ) { // 当前节点有右子节点
            
            if (heap[max] < heap[i*2+2]) { // 右子节点更大
                
                max = i * 2 + 2;
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
        
        shiftDownToMaxHeap(heap,i,length);
        
        
    }
    
}

/** 排序 , 从小到大*/
void hSortMinToMax(int heap[],int length){
    
    
    while (length > 1) {
        
        // 堆的首尾交换
        int end = length -1 ;
        heap[0] = heap[0]^heap[end];
        heap[end] = heap[0]^heap[end];
        heap[0] = heap[0]^heap[end];
        
        // 堆尾已是最大值,排除,对剩余部分继续排序
        length--;
        
        // 堆首向下调整,使其满足最大堆特性
        shiftDownToMaxHeap(heap, 0, length);
        
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
    hSortMinToMax(heap,length);
    
    
    // >排序后输出
    printf("排序后\n");
    for (int i = 0; i < length; i++) {
        printf("%d ",heap[i]);
    }
    printf("\n");
    printf("******************************\n");
}


/*****************************************/


/**********堆排序--前 K 大的数*********************/

#pragma mark - 堆排序--TopK

/**
 *  对非叶结点 i 向下调整,使其符合最小堆特性 , i 从0开始
 *
 *  @param a 二叉树
 *  @param i 待调整节点编号
 */
void shiftDownToMinHeap(int heap[],int i,int length){
    
    BOOL flag = FALSE; // 标记是否已是最小堆
    while( (i*2 + 1 <= length-1) && flag == FALSE ){ // 当前节点有左子节点,且需要向下调整
        
        int min ; // 当前节点及其子节点中最大的节点编号
        if (heap[i] > heap[i*2+1]) { // 当前节点大于左子节点
            
            min = 2*i+1;
            
        }else{
            
            min = i;
        }
        
        if ( (i*2+2) <= length-1 ) { // 当前节点有右子节点
            
            if (heap[min] > heap[i*2+2]) { // 右子节点更小
                
                min = i * 2 + 2;
            }
            
        }
        
        if (min != i ) { // 最小的节点不是自己,进行交换
            
            // 异或交换两个数
            heap[i] = heap[i]^heap[min];
            heap[min] = heap[i]^heap[min];
            heap[i] = heap[i]^heap[min];
            
            i = min; // 继续向下调整
        } else{
            
            flag = TRUE; // 已是最小堆
        }
        
        
        
    }
    
}


/** 创建最小堆 */
void creatMinHeap(int heap[],int length){
    
    for (int i = length * 0.5 - 1; i >= 0; i--) { // 二叉树的非叶节点
        
        shiftDownToMinHeap(heap,i,length);
        
        
    }
    
}

/** 排序 , 从大到小 */
void hSortMaxToMin(int heap[],int length){
    
    
    while (length > 1) {
        
        // 堆的首尾交换
        int end = length -1 ;
        heap[0] = heap[0]^heap[end];
        heap[end] = heap[0]^heap[end];
        heap[0] = heap[0]^heap[end];
        
        // 堆尾已是最小值,排除,对剩余部分继续排序
        length--;
        
        // 堆首向下调整,使其满足最小堆特性
        shiftDownToMinHeap(heap, 0, length);
        
    }
    
    
}


/**
 *  利用堆特性, 找出前 K 大的数
 *
 *  @param a      给定数组
 *  @param length 数组长度
 *  @param K
 */
void heapSortTopK(int a[],int length, int K){
    
    
    printf("***********最小堆排序--Top K 问题**************\n");
    // >排序前
    printf("给定数组:\n");
    for (int i = 0; i < length; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    
    
    // 取出前 K 个数,建立最小堆
    int minHeap[K];
    for (int i=0; i<K; i++) {
        minHeap[i] = a[i];
    }
    creatMinHeap(minHeap, K);
    
    for (int i=K; i<length; i++) { // 遍历剩余元素
        
        if(minHeap[0] >= a[i])
            continue;
        
        // a[i] > a[0] , 更新堆
        minHeap[0] = a[i];
        shiftDownToMinHeap(minHeap, 0, K);
        
    }
    
    hSortMaxToMin(minHeap, K);
    
    printf("前 %d 大的数:\n",K);
    for (int i=0; i<K; i++) {
        printf("%d ",minHeap[i]);
    }
    
    printf("\n");
    printf("******************************\n");

}

/*****************************************/


/**********归并排序***********************/

#pragma mark - 归并排序

/** 二路合并 ***/
void merge(int a[],int temp[],int startIndex,int midIndex,int endIndex){
    
    int i = startIndex, j = midIndex + 1, k = startIndex;
    
    // 左右两路进行比较合并
    while ( (i != midIndex + 1) && (j != endIndex + 1)  ) {
        
        if (a[i] > a[j])
            temp[k++] = a[j++];
        else
            temp[k++] = a[i++];
        
    }
    
    // 把左右两路未参与比较合并的剩余元素放入临时数组
    while ( i!= midIndex + 1 ) { // 左路有剩余元素
        temp[k++] = a[i++];
    }
    while ( j!= endIndex + 1 ) {  // 右路有剩余元素
        temp[k++] = a[j++];
    }
    
    // 调整原数组归并好的部分
    for( i = startIndex; i <= endIndex; i++ ){
        a[i] = temp[i];
    }
    
}

/**归并*/
void mSort(int a[],int temp[],int startIndex,int endIndex){
    
    if (startIndex >= endIndex)
        return;
    
    // startIndex <  endIndex的情况
    // 递归拆分子序列
    int midIndex = (startIndex + endIndex) * 0.5;
    mSort(a, temp, startIndex, midIndex);
    mSort(a, temp, midIndex+1, endIndex);
    // 排序合并子序列
    merge(a, temp, startIndex, midIndex, endIndex);
    
    
}


void mergeSort(int a[],int length){
    
    printf("***********归并排序**************\n");
    // >排序前
    printf("给定数组:\n");
    for (int i = 0; i < length; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    
    int temp[length];
    
    mSort(a, temp, 0, length-1);
    
    // >排序后输出
    printf("排序后:\n");
    for (int i = 0; i < length; i++) {
        printf("%d ",a[i]);
    }
    printf("\n");
    printf("******************************\n");
    
}



/*****************************************/
