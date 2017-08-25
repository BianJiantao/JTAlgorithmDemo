//
//  geneticAlgorithm.c
//  JTAlgorithmDemo
//
//  Created by BJT on 17/8/24.
//  Copyright © 2017年 BJT. All rights reserved.
//

/**
 *  编码过程中的教训:
 *  1. 种群个体选择时,随机数可以取到 1 ,而个体的累积概率理论上最后一个个体的值应为 1 ,
 *    但是因为计算过程中,有数据类型转换,真实值是很接近于 1但要小于1 的浮点数,结果导致 indexForSelectObject 函数获取
 *    个体索引时,出现 返回默认的 -1 的情况, 种群数据就出现了混乱,要么是坏内存访问,要么是适应度计算出现各种问题
 *  2. 关于内存的
 *     编码起码,种群个体选择时, 临时存储选出的个体的数组,  gene 所用的内存一直用的是同一块内存, 选择完后又用临时
 *     结构体数组对种群的每一个个体进行赋值,而此时就会有多个个体的 gene 指向同一块内存,而后续的相关计算,会受到很大的影响
 *     ,所以临时存储的数组,也另外开辟了一块内存,以避免这个问题
 * 
 *  上述两个问题,第一版代码写完调试时,上述两个问题是同时存在的,导致花了很长时间去  debug .调试过程, 一开始只知道 2.内存的问题 ,
 *  因此先不用为 gene 动态申请内存,利用 gene[7] 数组,避免了内存引起的问题,从而发现了隐藏的很深的 第 1 个随机数的问题.
 * 
 *  调试过程很吐血,作为经验教训,做此记录.
 *
 **/


#include "geneticAlgorithm.h"
#include "common.h"

const int RandomMax = 10000;
const int Population_Size = 40; // 种群大小
const int Population_Max_Genrations = 500; // 进化总代数
const double Population_CrossProbability = 0.8; // 种群交叉概率
const double Population_MutateProbability = 0.15; // 种群变异概率

int GeneCount; // 基因个数, 对应物品个数
int Max_Weight; // 背包最大承重
BOOL *crossBook; // 用于标记已经交换的基因点,防止重复交换
BOOL *mutationBook; // 用于标记已经变异的基因点,防止重复交换

typedef struct {
    
    int *gene; // 基因,对应的问题的解 (用指针是为了依据外界传进来的基因个数,动态申请内存, 避免代码写死:gene[7]
    int fitness; // 适应度
    double selectProbability; // 选择概率
    double amassProbability; // 累积概率, 概率区间
    
} Population ; // 种群中的每个个体属性

Population tempPop[Population_Size];   // 用于临时存储选中的个体

void generateRandomGene( int *gene){
    
    for (int i=0; i<GeneCount; i++) {
        
        gene[i] = arc4random_uniform(2); // 随机生成 0,1
        
    }
}

void population_Initialize(Population *population){

    // 设置种群个体信息
    for (int i=0; i<Population_Size; i++) {
        
        generateRandomGene(population[i].gene);
        population[i].fitness = 0;
        population[i].selectProbability = 0;
        population[i].amassProbability = 0;
        
    }
    
}

int getBestFitnessObject(Population *population, Population *bestObject){
    
    int best = 0;
    for (int i=0; i<Population_Size; i++) {
        
        if ( population[i].fitness > population[best].fitness ) {
            
            best = i;
        }
    }
    if (bestObject != NULL) {
        *bestObject = population[best];
    }
    return  best;
}

void population_EnvaluateFitness(Population *population,int *weightArr,int *valueArr, int *populationFitnessSum){
    int i,j;
    int weight;
    *populationFitnessSum = 0 ; // 把上一代的归零
    
    for (i=0; i<Population_Size; i++) {
        
        population[i].fitness = 0; // 把上一代的归零
        weight = 0;
        
        for (j=0; j<GeneCount; j++) {
            
            if (population[i].gene[j]==1) { // 如果为 1 ,即选中相应物品
                population[i].fitness += valueArr[j];
                weight += weightArr[j];
            }
        }
        if ( weight > Max_Weight ) { // 当前个体的物品总重超过背包容量,进行 适应度惩罚
            
            population[i].fitness = 1;
        }
        (*populationFitnessSum) += population[i].fitness;
        
    }
}

int indexForSelectObject(Population *population,double randomP){  // 轮盘赌的方式选择
    
    
    double a[Population_Size];
    for (int i=0; i<Population_Size; i++) {
        a[i] = population[i].amassProbability;
    }
    
    if(randomP <= population[0].amassProbability){ // 随机数落在第一个个体的概率区间内
        
        return 0;
        
    }else{  // 随机数落在其他个体的概率区间
        
        for ( int j=0; j<Population_Size; j++) {
            
            if ( (randomP > population[j].amassProbability)
                &&(randomP <= population[j+1].amassProbability) ) {
                return (j+1);
            }
        }
    }

    return getBestFitnessObject(population, NULL); // return -1 避免坏内存访问,不返回-1.默认返回当前适应度最好的那一个,正常情况下,不会来到这一步.如果来到这一步,说明代码存在问题
}

void copyPopulationData(Population *srcPop,Population *destPop){
    
    destPop->amassProbability = srcPop->amassProbability;
    destPop->selectProbability = srcPop->selectProbability;
    destPop->fitness = srcPop->fitness;
    memcpy(destPop->gene, srcPop->gene, sizeof(int)*GeneCount);
    
}

void population_Select(Population *population,int fitnessSum){ // 选择个体进行进化
    
    int i;
    // 计算每一个个体的选择概率和累积概率
    double amssTemp = 0;
    for (i=0; i<Population_Size; i++) {
        
        population[i].selectProbability = (double)(population[i].fitness) / fitnessSum;
        population[i].amassProbability = amssTemp + population[i].selectProbability;
        amssTemp = population[i].amassProbability;
        
    }
    population[Population_Size-1].amassProbability = 1; // 此处很重要: 防止后面选择时,随机数为1,产生不必要的麻烦
    
    int selectIndex = 0;  // 选中的个体编号
    // 选择个体
    double randomP = 0.0;
    for ( i=0; i<Population_Size; i++) {
        
        randomP = (double)arc4random_uniform(RandomMax) / RandomMax; // 随机生成一个 [0,1) 之间的数
        selectIndex = indexForSelectObject(population, randomP); // 获取选中的个体编号
        copyPopulationData(&population[selectIndex],&tempPop[i]); // 临时存储选中的个体数据
    }
    
    for (i=0; i<Population_Size; i++) {
        
        copyPopulationData(&tempPop[i], &population[i]); // 对种群重新赋值
    }
    
}

void exchangeGenePoint(Population *population,int first,int second){ // 随机交换多个基因点,
    
    int pointNum = arc4random_uniform(GeneCount-1)+2; // 要交换的基因点数 >=2
    int point = 0;
    int temp = 0;
    memset(crossBook, FALSE, GeneCount * sizeof(BOOL)); // 重置
    
    for (int i=0; i<pointNum; i++) {
        
        // 随机获取到交换的基因点位置
        point = arc4random_uniform(GeneCount);
        while (crossBook[point] == TRUE) { // 该点已经交换过,再换一个点
            point = arc4random_uniform(GeneCount);
        }
        crossBook[point] = TRUE; // 标记该点已交换
        temp = population[first].gene[point] ;
        population[first].gene[point] = population[second].gene[point];
        population[second].gene[point] = temp;
        
    }
    
}

void population_Cross(Population *population){ // 种群交叉 ,多点交叉 , >=2
    
    double randomCrossP = 0.0;
    int indexOfFirstObjct = -1; // 交叉的第一个个体的索引
    for (int i=0; i<Population_Size; i++) {
        
        randomCrossP = (double)arc4random_uniform(RandomMax) / RandomMax ;
        
        if ( randomCrossP < Population_CrossProbability ) { // 小于交叉概率,当前个体可以交叉
            
            if (indexOfFirstObjct < 0) { // 还没有找到第一个交叉的个体
                
                indexOfFirstObjct = i; // 标记第一个交叉的个体
                
            }else{  // 找到了两个交叉的个体  indexOfFirstObjct,i
                
                exchangeGenePoint(population,indexOfFirstObjct,i); // 交换基因点
                indexOfFirstObjct = -1; //  标记重置,便于标记后续个体
            }
            
            
        }
        
    }
    
}

void mutationGenePoint(Population *population,int index){
    
    int pointNum = arc4random_uniform(GeneCount)+1; // 要变异的基因点数
    int point = 0; // 要变异的基因位置
     memset(mutationBook, FALSE, GeneCount * sizeof(BOOL)); // 重置
    
    for (int i=0; i<pointNum; i++) {
        
        point = arc4random_uniform(GeneCount);
        while (mutationBook[point] == TRUE) { // 该点已经变异过,再换一个点
            point = arc4random_uniform(GeneCount);
        }
        mutationBook[point] = TRUE; // 标记该基因点已经变异
        population[index].gene[point] = 1 - population[index].gene[point]; // 变异: 0,1 取反
        
    }
}

void population_Mutation(Population *population){ // 种群变异 ,均匀变异
    
    double randomMutationP = 0.0;
    
    for (int i=0; i<Population_Size; i++) {
        
        randomMutationP = (double)arc4random_uniform(RandomMax+1) / RandomMax ;
        if( randomMutationP < Population_MutateProbability ){ // 小于变异概率,可以变异
            
            mutationGenePoint(population,i);
        }
        
    
    }
    
    
}


void knapsackProblemWithGA(int *weightArr,int *valueArr,int count, int MaxWeight){
   
    // 输出初始信息
    printf("************* 遗传算法解 0/1 背包问题****************\n");
    
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
    
    GeneCount = count;
    Max_Weight = MaxWeight;
    Population population[Population_Size];
    // 申请内存
    for (int i=0; i<Population_Size; i++) {
        
        population[i].gene = (int *)malloc(GeneCount * sizeof(int));
        tempPop[i].gene = (int *)malloc(GeneCount * sizeof(int));
        
    }
    crossBook = (BOOL *)malloc(GeneCount * sizeof(BOOL));
    mutationBook = (BOOL *)malloc(GeneCount * sizeof(BOOL));
    
    int populationFitnessSum = 0; // 种群总的适应度,用于计算每个个体的概率
    // 初始化种群
    population_Initialize(population);
    
    // 适应度函数,计算种群每个个体的适应度
    population_EnvaluateFitness(population,weightArr,valueArr,&populationFitnessSum);
    for(int i=0; i< Population_Max_Genrations;i++){
        
        population_Select(population,populationFitnessSum); // 选择要进行进化的个体
        population_Cross(population); // 多点交叉
        population_Mutation(population); // 均匀变异
        population_EnvaluateFitness(population, weightArr, valueArr, &populationFitnessSum); // 更新进化后的适应度
    }
    
    // 进化完毕,查找适应度最好的个体
    Population bestObject;
    getBestFitnessObject(population,&bestObject);
    
    // 输出计算结果
    int bestCount = 0; // 种群中进化到最优解的个体数目
    for(int i=0; i<Population_Size;i++ ){
        
        if(population[i].fitness == bestObject.fitness)
            bestCount++;
    }
    
    
    if(bestObject.fitness){
        
        printf("❗️--找到最优解,总价值: %d\n被装进背包的物品如下:\n" , bestObject.fitness);
        
        for (int i=0; i<GeneCount; i++) {
            
            if (bestObject.gene[i]==1) { // 选中 i 商品
                
                printf("编号: %d  重量: %d  价值: %d\n",i+1, weightArr[i], valueArr[i]);
                
            }
            
        }
        
        
        
    } else{
        
        printf("❌--未找到最优解\n");
    }
    
    printf("********************************************\n");
    
    // 释放内存
    for (int i=0; i<Population_Size; i++) {
        
        free(population[i].gene);
        free(tempPop[i].gene);
        
    }
    free(crossBook);
    free(mutationBook);
    
}






