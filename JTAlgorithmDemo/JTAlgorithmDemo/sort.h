//
//  sort.h
//  JTAlgorithmDemo
//
//  Created by BJT on 17/8/14.
//  Copyright © 2017年 BJT. All rights reserved.
//  排序方法

#ifndef sort_h
#define sort_h

#include <stdio.h>


#include "common.h"


/**
 *  桶排序
 *
 *  @param a      待排序数组
 *  @param length 数组长度
 *  @param max    数组中值的上限
 */
void bucketSort(int a[],int length, int max);
/**
 *  冒泡排序
 *
 *  @param a      待排序数组
 *  @param length 数组长度
 */
void bubbleSort(int a[], int length);

/**
 *  快速排序
 *
 *  @param a      待排序数组
 *  @param length 数组长度
 */
void quickSort(int a[], int length);

/**
 *   最大堆排序
 *
 *  @param a      待排序数组
 *  @param length 数组长度
 */
void  maxHeapSort(int a[],int length);

/**
 *  利用堆特性, 找出前 K 大的数
 *
 */
void heapSortTopK(int a[],int length, int K);

#endif /* sort_h */









