//
//  geneticAlgorithm.c
//  JTAlgorithmDemo
//
//  Created by BJT on 17/8/24.
//  Copyright © 2017年 BJT. All rights reserved.
//

#include "geneticAlgorithm.h"
#include "common.h"

const int RandomMax = 10000;
const int Population_Size = 40; // 种群大小
const int Population_Max_Genrations = 500; // 进化总代数
const double Population_CrossProbability = 0.8; // 种群交叉概率
const double Population_MutateProbability = 0.15; // 种群变异概率

const int GeneCount = 7; // 基因个数, 对应物品个数
int Max_Weight; // 背包最大承重
BOOL crossBook[GeneCount]; // 用于标记已经交换的基因点,防止重复交换
BOOL mutationBook[GeneCount]; // 用于标记已经变异的基因点,防止重复交换

typedef struct {
    
    int gene[GeneCount]; // 基因,对应的问题的解 (用指针是为了依据外界传进来的基因个数,动态申请内存, 避免代码写死:gene[7]
    int fitness; // 适应度
    double selectProbability; // 选择概率
    double amassProbability; // 累积概率, 概率区间
    
} Population ; // 种群中的每个个体属性

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
    
    if(randomP <= population[0].amassProbability){ // 随机数落在第一个个体的概率区间内
        
        return 0;
        
    }else{  // 随机数落在其他个体的概率区间
        
        for ( int j=0; j<Population_Size; j++) {
            
            if ( (randomP > population[j].amassProbability)
                &&(randomP < population[j+1].amassProbability) ) {
                return (j+1);
            }
        }
    }
    
    return -1;
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
    
    int selectIndex = 0;
    Population newPopulation[Population_Size]; // 临时存储选中的个体
    // 选择个体
    double randomP = 0.0;
    for ( i=0; i<Population_Size; i++) {
        
        randomP = (double)arc4random_uniform(RandomMax+1) / RandomMax; // 随机生成一个 [0,1] 之间的数
        selectIndex = indexForSelectObject(population, randomP); // 获取选中的个体编号
    
        newPopulation[i] = population[selectIndex];
    }
    
    for (i=0; i<Population_Size; i++) {
        
        population[i] = newPopulation[i]; // 对种群重新赋值
    }
    
}

void exchangeGenePoint(Population *population,int first,int second){ // 随机交换多个基因点,
    
    int pointNum = arc4random_uniform(GeneCount-1)+2; // 要交换的基因点数 >=2
    int point = 0;
    int temp = 0;
    memset(crossBook, FALSE, sizeof(crossBook)); // 重置
    
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
        
        randomCrossP = (double)arc4random_uniform(RandomMax+1) / RandomMax ;
        
        if ( randomCrossP < Population_CrossProbability ) { // 当前个体可以交叉
            
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
     memset(mutationBook, FALSE, sizeof(mutationBook)); // 重置
    
    for (int i=0; i<pointNum; i++) {
        
        point = arc4random_uniform(GeneCount);
        while (mutationBook[point] == TRUE) { // 该点已经交换过,再换一个点
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
        if( randomMutationP < Population_MutateProbability ){ // 可以变异
            
            mutationGenePoint(population,i);
        }
        
    
    }
    
    
}

void getBestFitnessObject(Population *population, Population *bestObject){
    
    int best = 0;
    for (int i=0; i<Population_Size; i++) {
        
        if ( population[i].fitness > population[best].fitness ) {
            
            best = i;
        }
    }
    *bestObject = population[best];
    
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
    
    Max_Weight = MaxWeight;
    Population population[Population_Size];
    
    int populationFitnessSum = 0;
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

    
}






