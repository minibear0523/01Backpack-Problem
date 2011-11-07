//
//  main.c
//  BackPack
//
//  Created by shadowdai on 11-10-25.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#include <stdio.h>

//k是开始字符的位置，n是数组的长度,l是子集的位数
void subArray(int W[], int V[], int k,int l, int n);

//初始化整个子集数组
void initArray(int n);

//用于输出子集的数组
int priArray[4];
void printArray(int W[], int n);

//计算子集的个数
int counter;
int subArrayWeight[16];
int subArrayValue[16];

//计算子集的重量和价值
void sumOfWeightAndValue(int W[], int V[], int m, int n);

//寻找重量不超过背包重量，并且价值最大的子集
int searchMax();

//重量和价值数组


int main()
{
	int i;
    int max;
	
	int array[4] = {7, 3 , 4, 5};
    int value[4] = {42, 12, 40, 25};
    
    //0是所有数组的子集
    printf("The No.1 is: 0\n");
    subArrayWeight[0] = 0;
    subArrayValue[0] = 0;
    counter = 1;
	
	for (i = 0; i < 4; i++)
	{
        initArray(4);
		//递归算法需要保证从第一个元素开始的所有的元素都被遍历到
		priArray[0] = i;
        counter ++;
        sumOfWeightAndValue(array, value, counter, 1);
		printArray(array, 1);
		subArray(array, value, i+1, 2, 4);	
	}
    
    printf("\nThere are %d SubArray.\n", counter);
    
    for (i = 0; i < 16; i++)
    {
        printf("The Weight of %d is %d and the value is %d\n", i+1 , subArrayWeight[i], subArrayValue[i]);
    }
    
    max = searchMax();
    printf("\nThe most valuable package is No.%d, the max value is %d.\n", max+1, subArrayValue[max]);
    
	return 0;
}

/*
 * 该递归算法每次只向后寻找一位数字。
 * 例如k=1时，只会寻找2，3，4;k=2时，只会寻找3，4
 */

void subArray(int W[], int V[], int k, int l, int n)
{
	int i;
	
	if (k == n-1)
	{
        //n是整个数组的长度，k是整个子集的上一位字符，当k == n-1时，意味着已经是最后一个了。
        priArray[l-1] = k;
        counter += 1;
        sumOfWeightAndValue(W, V, counter, l);
		printArray(W, l);
	}
	else
	{
		for ( i= k; i <= n-1; ++i)
		{
			priArray[l-1] = i;
            counter += 1;
            sumOfWeightAndValue(W, V, counter, l);
			printArray(W, l);
			subArray(W, V, i+1, l+1,n);
		}
	}
	
}

/*
 * 打印子集数组的函数
 */

void printArray(int W[], int n)
{
	int i;
    
    printf("The No.%d is: " , counter);
    
	for (i = 0; i < n; i++)
	{
		printf("%d	", W[priArray[i]]);
	}
	printf("\n");
}

/*
 * 初始化子集数组
 */
void initArray(int n)
{
    for (int i = 0; i<= n-1 ; i++) {
        priArray[i] = 0;
    }
}

/*
 * 计算子集的重量和价值综合
 * m是该子集的序号，与counter相同。n是数组长度
 */
void sumOfWeightAndValue(int W[], int V[], int m, int n)
{
    int i;
    int sumWeight = 0, sumValue = 0;//重量和价值总和变量
    for ( i = 0; i < n; i++) {
        sumWeight += W[priArray[i]];
        sumValue += V[priArray[i]];
    }
    subArrayWeight[m-1] = sumWeight;
    subArrayValue[m-1] = sumValue;
}

/*
 * 排序并查找所有子集中最大子集
 */
int searchMax()
{
    int i,max,MAX;
    max = 0;
    MAX = subArrayValue[max];
    
    for (i = 0; i < 16; i++) {
        if (subArrayWeight[i] <= 10) 
        {
            if (subArrayValue[i] >= MAX)
            {
                max = i;
                MAX = subArrayValue[max];
            }
        }
    }
    
    return max;
}