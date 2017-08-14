//
//  main.c
//  JTAlgorithmDemo
//
//  Created by BJT on 17/8/14.
//  Copyright © 2017年 BJT. All rights reserved.
//

#include <stdio.h>

#include "sort.h"
/**
 * 排序类型
 */
typedef enum {
    
    SortTypeBucket, // 桶排序
    SortTypeBubble, // 冒泡排序
    SortTypeQuick // 快速排序
    
}SortType;




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
            // 1> 桶排序
                bucketSort(array, arrayLength, maxValue+1);
            break;
        case SortTypeBubble:
            // 2> 冒泡排序
                bubbleSort(array, arrayLength);
            break;
        case SortTypeQuick:
            // 3> 快速排序
            quickSort(array, arrayLength);
            break;
            
        default:
            break;
    }
    
    /******************************************************/
    
    
}

int main() {
    
    sortGo(SortTypeQuick);
    
    
    return 0;
    
}
