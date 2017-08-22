//
//  dynamicProgramming.c
//  JTAlgorithmDemo
//
//  Created by BJT on 17/8/18.
//  Copyright © 2017年 BJT. All rights reserved.
//


#include <ctype.h>

#include "dynamicProgramming.h"
#include "common.h"

/**********0-1背包问题***********************************/

#pragma mark - 0/1 背包问题 Knapsack Problem

#pragma mark 动态规划法

/**
 *  动态规划法处理背包问题
*/

void knapsackProblemWithDP(int *weightArr,int *valueArr,int count, int MaxWeight){
    
    // 输出初始信息
    printf("************* 动态规划法处理 0/1 背包问题****************\n");
    
    printf("物品编号: ");
    for (int i=0; i<count; i++) {
        
        printf("%3d ",i+1);
    }
    printf("\n");
    
    printf("物品重量: ");
    for (int i=0; i<count; i++) {
        
        printf("%3d ",weightArr[i]);
    }
    printf("\n");
    printf("物品价值: ");
    for (int i=0; i<count; i++) {
        
        printf("%3d ", valueArr[i]);
    }
    printf("\n❓--背包最大承重: %d\n",MaxWeight);
    
    // 求最优解
    int row = count + 1;  // 行: 0 1 2 ... count
    int col = MaxWeight + 1; // 列: 0 1 2 3 ...MaxWeight
    
    int maxValueArr[row][col]; // 二维数组 maxValueArr[i][j], 表示  背包最大容量为 j 时,前 i 个物品进行放入所能取得的最大价值
    
    int maxValue_i_1_j;
    int maxValue_i_j;
    
    for (int i=0; i<row; i++) {
        
        for(int j=0; j<col; j++){
            
            if ( i==0 || j==0) { // 第一行,或第一列 置为 0
                
                maxValueArr[i][j] = 0;
                
            }else if(weightArr[i-1] > j){  // 第 i 个物品重量大于背包承重, 即装不下 i
               
                maxValueArr[i][j] = maxValueArr[i-1][j];
                
            }else{
                
                maxValue_i_1_j = maxValueArr[i-1][j]; // 不放 i
                maxValue_i_j = maxValueArr[i-1][j-weightArr[i-1]] + valueArr[i-1]; //  放 i
                
                maxValueArr[i][j] = max_int( maxValue_i_1_j , maxValue_i_j );
                
            }
            
            
            
        }
        
    }
    
    
    // 输出计算结果
    int optValue = maxValueArr[count][MaxWeight];
    
    if ( optValue ) {
        
        printf("❗️--找到最优解,总价值: %d\n被装进背包的物品如下:\n" , optValue);
        
        int i = count , j = MaxWeight;
        int maxValue_i_j;
        
        while (i>0) { // 查找被选中的物品
            
            maxValue_i_j = maxValueArr[i-1][j-weightArr[i-1]] + valueArr[i-1];
            if (maxValueArr[i][j] == maxValue_i_j) { // i 被选中
                
                printf("编号: %d  重量: %d  价值: %d\n",i, weightArr[i-1], valueArr[i-1]);
                j -= weightArr[i-1];
                
            }
            
            i--;
        }
        
    } else{
        
        printf("❌--未找到最优解\n");
    }
    
    printf("********************************************\n");
    
}


#pragma mark 回溯法

int backtracking_optValue = 0, // 最优值
    backtracking_currentWeight = 0, // 背包当前重量
    backtracking_currentValue = 0; // 背包当前价值

BOOL  *tempBook,  // tempBook[] 存储每一个状态空间解向量的中间变量
      *book;  // book[] 最优解 , 标记所有选中的物品, true 表示选中, false 表示不选

void backtracking(int *weightArr,int *valueArr,int count, int MaxWeight, int i){

    if( i > count){ // 搜索完毕解空间中的一个解
        
        
        if(backtracking_currentValue > backtracking_optValue){ // 更新最优值
            
            backtracking_optValue = backtracking_currentValue;
            
            for (int i=0; i<count; i++) {
                
                book[i] = tempBook[i]; // 更新最优解
            }
            
        }
        
        return;
    }
    
    if (backtracking_currentWeight + weightArr[i-1] <= MaxWeight ) { // 可以装下 i , 搜索解空间状态树的左子树
        
        backtracking_currentWeight += weightArr[i-1];
        backtracking_currentValue += valueArr[i-1];
        tempBook[i-1] = 1;
        
        backtracking(weightArr, valueArr, count, MaxWeight, i+1);
        
        backtracking_currentWeight -= weightArr[i-1]; // 恢复左子树前的状态
        backtracking_currentValue -= valueArr[i-1];
        tempBook[i-1] = 0;
    }
    
    backtracking(weightArr, valueArr, count, MaxWeight, i+1); // 搜索解空间状态树的右子树 ,(此处可以加一个上界函数,对状态树进行剪枝,判断是否要进入右子树搜索,提高搜索效率)
    
    
}

void knapsackProblemWithBacktracking(int *weightArr,int *valueArr,int count, int MaxWeight){
    
    // 输出初始信息
    printf("************* 回溯法解 0/1 背包问题****************\n");
    
    printf("物品编号: ");
    for (int i=0; i<count; i++) {
        
        printf("%3d ",i+1);
    }
    printf("\n");
    
    printf("物品重量: ");
    for (int i=0; i<count; i++) {
        
        printf("%3d ",weightArr[i]);
    }
    printf("\n");
    printf("物品价值: ");
    for (int i=0; i<count; i++) {
        
        printf("%3d ", valueArr[i]);
    }
    printf("\n❓--背包最大承重: %d\n",MaxWeight);
    
    // 初始化
    tempBook = (BOOL *)malloc(count * sizeof(BOOL));
    memset(tempBook, FALSE, count * sizeof(BOOL));
    
    book = (BOOL *)malloc(count * sizeof(BOOL));
    memset(book, FALSE, count * sizeof(BOOL));
    
    // 回溯
    backtracking(weightArr, valueArr, count, MaxWeight,1);
    
   // 输出计算结果
    if(backtracking_optValue){
        
        printf("❗️--找到最优解,总价值: %d\n被装进背包的物品如下:\n" , backtracking_optValue);
        
        for (int i=0; i<count; i++) {
           
            if (book[i]) { // 选中 i 商品
                
                printf("编号: %d  重量: %d  价值: %d\n",i+1, weightArr[i], valueArr[i]);
                
            }
            
        }
        
        
        
    } else{
        
        printf("❌--未找到最优解\n");
    }
    
    printf("********************************************\n");
    
    free(tempBook); // 释放内存
    free(book);
}

/*****************************************************/



/********** 字符串编辑距离 Levenshtein Distance ***********************************/

#pragma mark - 字符串编辑距离 Levenshtein Distance

#pragma mark 纯递归方法

/**
 *  字符串转小写
 */
char *toLowerString(char *string){

//    // string 可修改的情况下,可以这样转小写
//    for(int i=0; string[i]!= '\0'; i++){
//        
//        string[i] = tolower(string[i]);
//    }
//    
//    return string;
    
    // 如果 string 是字符串常量,上述方法不行,因为不能修改
    int len = (int)strlen(string)+1 ; // + 1 表示 字符串结束符 '\0'
    char *lower = (char *)malloc(sizeof(char)*len); // 申请内存
    
    for (int i=0; i<len-1; i++) {
        
        lower[i] = tolower(string[i]);
        
    }
    lower[len-1] = '\0'; // 末尾添加 字符串结束符 '\0'
    
    return lower;
    
}



/**
 *  递归计算最小编辑距离
 */
int pureRecursion(char *src,char *dest){
    
    if ( strlen(src)==0 || strlen(dest)==0 ) { // 其中一个字符串 剩余子串长度为0
        
        int len = (int)(strlen(src) - strlen(dest));
        return abs( len );
        
    }else if( src[0] == dest[0] ){ // 剩余子串首字母相同,各后移一位
        
        return pureRecursion(src+1, dest+1);
        
    }else{ // 首字母不同, 进行 插入,删除,替换
        
        int insertDis = pureRecursion(src, dest+1) + 1; // 插入 , 比如:  A B C / D E F --> D, A B C / D, E F
        int deleteDis = pureRecursion(src+1, dest) + 1 ; // 删除, 比如: A B C / D E F -->  B C / D E F
        int replaceDis = pureRecursion(src+1, dest+1) + 1; // 替换, 比如: A B C / D E F --> D B C / D E F
        
        return min_int((min_int(insertDis, deleteDis)), replaceDis); // 返回 插入,删除,替换 中的最小距离
        
    }
    
}


int levenshteinDistanceWithPureRecursion(char *sourceString,char *destString){
    
    // 输出初始信息
    printf("************* 纯递归法计算字符串编辑距离 ****************\n");
    printf("❓源字符串:   %s\n❓目标字符串: %s\n",sourceString,destString);
    
    // 全转为小写
    char *srcLowerStr = toLowerString(sourceString);
    char *destLowerStr = toLowerString(destString);
    
    // 递归计算编辑距离
    int distance = pureRecursion(srcLowerStr,destLowerStr);
    
    
    // 输出结果
    printf("❗️最小编辑距离为: %d\n",distance);
    
    printf("********************************************\n");
    
    free(srcLowerStr); // 释放内存
    free(destLowerStr);
    
    return distance;
}

#pragma mark 优化递归方法

typedef struct {
    
    int distance; // 当前状态字符串的编辑距离
    int stateCount; // 当前状态出现的次数
    
}LD_Book; // 每次递归时 字符串状态信息

LD_Book **ld_book; //  ld_book[i][j] 存储每一次字符串递归时的状态

int optimizeRecursion(char *sourceString,char *destString, int srcIndex, int destIndex){
    
        
    if( ld_book[srcIndex][destIndex].stateCount != 0 ){ // 该状态已出现过,不再计算,直接返回
        
        ld_book[srcIndex][destIndex].stateCount++;
        return ld_book[srcIndex][destIndex].distance;
        
    }
    
    int distance = 0;
    if ( strlen(sourceString+srcIndex)==0 || strlen(destString+destIndex)==0 ) { // 其中一个字符串 剩余子串长度为0
        
        int len = (int)( strlen(sourceString+srcIndex) - strlen(destString+destIndex) );
        distance = abs( len ) ;
     
    }else if( sourceString[srcIndex] == destString[destIndex] ){ // 剩余子串首字母相同,各后移一位
        
        distance = optimizeRecursion(sourceString, destString, srcIndex+1, destIndex+1);
        
    }else{ // 首字母不同, 进行 插入,删除,替换
        
        int insertDis = optimizeRecursion(sourceString, destString, srcIndex, destIndex+1) + 1; // 插入 , 比如:  A B C / D E F --> D, A B C / D, E F
        int deleteDis = optimizeRecursion(sourceString, destString, srcIndex+1, destIndex) + 1 ; // 删除, 比如: A B C / D E F -->  B C / D E F
        int replaceDis = optimizeRecursion(sourceString, destString, srcIndex+1, destIndex+1) + 1; // 替换, 比如: A B C / D E F --> D B C / D E F
        
        distance =  min_int((min_int(insertDis, deleteDis)), replaceDis); // 返回 插入,删除,替换 中的最小距离
        
    }
    
    ld_book[srcIndex][destIndex].distance = distance; // 记录当前状态
    ld_book[srcIndex][destIndex].stateCount = 1;
    
    
    return distance;
}


int levenshteinDistanceWithOptimizeRecursion(char *sourceString,char *destString){
    
    printf("************* 优化递归法计算字符串编辑距离 ****************\n");
    printf("❓源字符串:   %s\n❓目标字符串: %s\n",sourceString,destString);
    // 全转为小写
    char *srcLowerStr = toLowerString(sourceString);
    char *destLowerStr = toLowerString(destString);
    
//    int rowCol = min_int((int)strlen(srcLowerStr), (int)strlen(destLowerStr));
    int row = (int)strlen(srcLowerStr) + 1 ; // + 1 是为了避免当其中一个字符串递归到末尾 '\0' 时,数组访问越界
    int col = (int)strlen(destLowerStr) + 1 ;
    
    ld_book = (LD_Book* *)malloc(row * sizeof(LD_Book *));
    for (int i=0; i<row; i++) {
        
        ld_book[i] = (LD_Book *)malloc( col * sizeof(LD_Book) ); // 为 ld_book[i]  的每一行申请内存
        
        for(int j =0 ; j<col; j++){  // ld_book 初始化
            
            ld_book[i][j].distance = 0;
            ld_book[i][j].stateCount = 0;
            
        }
    }
    
    
    // 递归计算
    int distance = optimizeRecursion(srcLowerStr, destLowerStr, 0, 0);
    
    
    // 输出结果
    printf("❗️最小编辑距离为: %d\n",distance);
    
    printf("状态记录矩阵: 各个状态的出现次数(大于1的状态进行了优化)\n");
    for (int i=0; i<row; i++) {
        for (int j=0; j<col; j++) {
            
            
            printf("%3d ", ld_book[i][j].stateCount); // 打印各个状态的重复次数,相比于单纯的递归,大于1的状态进行了优化,
            
        }
        printf("\n");
    }
    
    printf("********************************************\n");
    
    // 释放内存
    free(srcLowerStr);
    free(destLowerStr);
    
    for (int i=0; i<row; i++) {
        free(ld_book[i]);
    }
    free(ld_book);
    
    return distance;
}


#pragma mark 动态规划法

int levenshteinDistanceWithDP(char *sourceString,char *destString){
    
    printf("************* 动态规划法计算字符串编辑距离 ****************\n");
    printf("❓源字符串:   %s\n❓目标字符串: %s\n",sourceString,destString);
    // 全转为小写
    char *srcLowerStr = toLowerString(sourceString);
    char *destLowerStr = toLowerString(destString);
    
    int row = (int)strlen(srcLowerStr) + 1 ; // + 1 是考虑到空串的情形
    int col = (int)strlen(destLowerStr) + 1 ;
    
    int dis[row][col];  // dis[i][j]  源字符串 1-i 与目标字符串 1-j 的最小编辑距离
    
    // dis 初始化
    for(int i=0; i<col; i++) // 第一行 , 源字符串是空串
        dis[0][i] = i;
    for(int i=0; i<row; i++) // 第一列,  目标字符串是空串
        dis[i][0] = i;
    
    
    for (int i=1; i<row; i++) {
        
        for (int j=1; j<col; j++) {
            
            
            if ( srcLowerStr[i-1] == destLowerStr[j-1] ) { // 末字符相等
                
                dis[i][j] = dis[i-1][j-1];
                
            }else{ // 不相等,执行 插入/删除/替换 操作
                
                int insertDis = dis[i][j-1] + 1; // 1,i  --> 1,j-1 , 最后一位 j 插入到末尾
                int deleteDis = dis[i-1][j] + 1; // 1,i-1  --> 1,j , 最后一位 i 删除
                int replaceDis = dis[i-1][j-1] + 1; // 1,i-1  --> 1,j-1 , 最后一位 i 替换为 j
                
                 dis[i][j] =  min_int((min_int(insertDis, deleteDis)), replaceDis); // 插入,删除,替换 中的最小距离
            }
            
            
        }
        
    }
    // 输出结果
    printf("❗️最小编辑距离为: %d\n",dis[row-1][col-1]);
    
    printf("********************************************\n");
    
    return dis[row-1][col-1];
}


/*****************************************************/


