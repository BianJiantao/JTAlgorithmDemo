//
//  threeBucket.c
//  JTAlgorithmDemo
//
//  Created by BJT on 17/8/21.
//  Copyright © 2017年 BJT. All rights reserved.
//

#include "threeBucket.h"
#include "common.h"

const int BucketCount = 3; // 水桶个数
const int MaxStateCount = 100; // 限制最大水桶状态数, 水桶状态栈的上限


BucketState Bucket_EndState; // 目标状态
int *Bucket_Capacity; // 水桶容量

typedef struct{
    
    BucketState *bucketStates; // 存储水桶状态的数组 [][3]
    int bucketStatesCount; // 存储的状态数 , 栈顶
    
}BucketStatesStack; // 水桶状态栈

BucketStatesStack states;


/**
 *  将 srcState 的水桶状态拷贝到 newState
 *
 */
void StateCopy(BucketState newState,BucketState srcState){
    
    for (int i=0; i<BucketCount; i++) {
        
        newState[i] = srcState[i];
    }
}

/**
 *  判断当前状态是否是目标状态
 *
 */
BOOL isEndState( BucketState currentState ){
    
    for (int i=0; i<BucketCount; i++) {
        
        if (currentState[i] != Bucket_EndState[i])
            return FALSE;
    }
    
    return TRUE;
}
/**
 *  判断当前水桶状态下,某一水桶是否是空桶
 *
 */
BOOL isEmptyBucket(BucketState currentState,int bucket){ //  currentState状态下, bucket 是否为空
    
    return  ( currentState[bucket] == 0 );
}

/**
 *  判断当前水桶状态下,某一水桶是否是满桶
 *
 */
BOOL isFullBucket(BucketState currentState,int bucket){ //  currentState状态下, bucket 是否已满
    
    return  ( currentState[bucket] == Bucket_Capacity[bucket] );
}

/**
 *  判断当前水桶状态下,判断是否可以从 fromBucket 向 toBucket 倒水
 *
 */
BOOL isCanDumpWater( BucketState currentState,int fromBucket,int toBucket ){
    
    if (fromBucket == toBucket) // 不能自己向自己桶中倒水,避免无谓的计算
        return FALSE;
    
    if ( !isEmptyBucket(currentState, fromBucket)
        && !isFullBucket(currentState, toBucket) ) { // fromBucket非空,toBucket不满
        
        return TRUE;
    }
    
    return FALSE;
}

/**
 * 从 currentState 状态,将 fromBucket 桶向 toBucket 倒水,得到新状态 newState
 *
 */
void  dumpWater( BucketState currentState,int fromBucket,int toBucket,BucketState newState){
    
    StateCopy(newState, currentState);
    
    int dumpWater =  Bucket_Capacity[toBucket] - currentState[toBucket];
    
    if (currentState[fromBucket] >= dumpWater ) { // 可以倒满 toBucket
        
        newState[fromBucket] -= dumpWater;
        newState[toBucket] += dumpWater;
        
    }else{ // fromBucket 可以倒完
        
        
        newState[toBucket] += currentState[fromBucket];
        newState[fromBucket] = 0;
        
    }
    
}

/**
 *  判断当前状态是否已在状态栈中存在
 *
 */
BOOL isExsitState(BucketState newState){
    
    int i,j,countFlag;  //  countFlag 标记相同状态的水桶个数
    BOOL flag = FALSE;
    BucketState tempState;
    for (i=0; i<states.bucketStatesCount; i++) {
        countFlag = 0 ;
        tempState = states.bucketStates[i];
        for (j=0; j<BucketCount; j++) {
            
            if ( tempState[j] != newState[j]  )
                break;
            countFlag++; // j 水桶状态一样
            
        }
        
        if (countFlag == BucketCount) { // 所有水桶的状态都相同, 则存在相同的状态 BucketState
            flag = TRUE;
            break;
        }
    }
    
    return flag;
}


int resultCount=0; // 可行方案数
int dumpCount[100]; // 存储各个方案的倒水次数,便于搜索结束时,查找最小倒水次数的方案

void searchState(){
    
    // 判断 当前状态是否是目标状态
    // 取出当前状态
    BucketState currentState = states.bucketStates[states.bucketStatesCount-1];
    if( isEndState(currentState) ){ // 是目标状态
       
        dumpCount[resultCount] = states.bucketStatesCount-1; // 存储各个方案的倒水次数
        printf("❗️方案: %d ,共需 %d 次操作\n",++resultCount,states.bucketStatesCount-1);
        // 输出倒水过程经历的状态
        for (int i=0; i<states.bucketStatesCount; i++) {
            
            currentState = states.bucketStates[i];
            printf("->( ");
            for (int j=0; j<BucketCount; j++) {
                
                printf("%d ",currentState[j]);
            }
            
            printf(")");
        }
        printf("\n");
        return;
    }
    
    // 不是目标状态, 进行倒水操作
    // 遍历6种倒水组合
    for (int i=0; i<BucketCount; i++) {
        
        for (int j=0; j<BucketCount; j++){
                
            if( isCanDumpWater(currentState, i, j) ){ // i,j 可以进行倒水操作
                
                // 借用 内存空间
                BucketState newState = states.bucketStates[states.bucketStatesCount] ;
                // 执行倒水操作,获取新的水桶状态
                dumpWater(currentState, i, j,newState);
                // 判断新状态是否已经存在
                if (!isExsitState(newState)) {
                    
                    states.bucketStatesCount++; // 新状态入栈
                    searchState(); // 继续状态搜索
                    states.bucketStatesCount--; // 尝试完毕,出栈
                    
                } ;
            }
            
            
        }
    }
    
}


void threeBucketProblemWithDfs(BucketState bucketStartState, BucketState bucketEndState, int * bucketCapacity){
    
    
    // 输出初始信息
    printf("************* 三个水桶等分水问题 ****************\n");
    printf("❓初始状态: ( ");
    for (int j=0; j<BucketCount; j++) {
        
        printf("%d ",bucketStartState[j]);
    }
    printf(") -> ");
    printf("目标状态: ( ");
    for (int j=0; j<BucketCount; j++) {
        
        printf("%d ",bucketEndState[j]);
    }
    printf(") 三个水桶容量: ( ");
    for (int j=0; j<BucketCount; j++) {
        
        printf("%d ", bucketCapacity[j]);
    }
    printf(")\n");
    
    
    // 申请内存
    states.bucketStates = (BucketState *)malloc(MaxStateCount * sizeof(BucketState));
    if(states.bucketStates == NULL) // 申请内存失败
        return;
    for (int i=0; i<MaxStateCount; i++) {
        
        states.bucketStates[i] = (BucketState)malloc(BucketCount * sizeof(int));
        if (states.bucketStates[i] == NULL)
            return;
    }
    
    // 初始化
    Bucket_Capacity = bucketCapacity;
    StateCopy(states.bucketStates[0],bucketStartState );// 存储初始状态到数组
    states.bucketStatesCount = 1;
    Bucket_EndState = bucketEndState; // 存储目标状态
    
    // 对水桶状态进行深度搜索
    searchState();
    
    // 查找最小倒水次数的方案
    int min = dumpCount[0];
    int sol = 1;
    for (int i=1; i<resultCount; i++) {
        if(min > dumpCount[i]){
            min = dumpCount[i];
            sol = i+1;
        }
    }
    printf("⭕️最小倒水次数是方案: %d,次数是: %d\n",sol,min);
    
    printf("********************************************\n");
    // 释放内存
    for (int i=0; i<MaxStateCount; i++) {
        free(states.bucketStates[i]);
    }
    free(states.bucketStates);
    
}