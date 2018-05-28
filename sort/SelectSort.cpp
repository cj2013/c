//选择排序，每次选在最小的一个放在序列起始位置
#include <iostream>
#include <cstdlib>
#include <stdio.h>
using namespace std;


void SelectSort(int* arr, int nCount)
{
	for(int i = 0; i < nCount - 1; i++)
	{
		int nMinIndex = i;
		for(int j = i + 1; j < nCount; j++)
		{
			if(arr[nMinIndex] > arr[j])
			{
				nMinIndex = j;
			}
		}
		
		int nTemp = arr[i];
		arr[i] = arr[nMinIndex];
		arr[nMinIndex] = nTemp;
	}
}

void OutPutArray(int* arr, int nCount)
{
	for(int i = 0; i < nCount; i++)
	{
		printf("--%d", arr[i]);
	}
	printf("\n");
}

int main()
{
	int arr[10] = {9,3,5,7,1,8,6,4,2,0};
	printf("origin array:\n");
	OutPutArray(arr, 10);
	
	printf("select sort result:\n");
	SelectSort(arr, 10);
	OutPutArray(arr, 10);
	return 0;
}