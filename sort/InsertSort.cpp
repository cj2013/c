//比如从小到大，直接插入在合适的位置
#include <iostream>
#include <cstdlib>
#include <stdio.h>
using namespace std;

//default:small to big
void InsertSort(int* arr, int nCount)
{
	for(int i = 1; i < nCount; i++)
	{
		//查找位置
		int ntemp = arr[i];
		int j = i-1;
		for(; j >= 0; j--)
		{
			if(arr[j] > ntemp)
			{
				arr[j + 1] = arr[j];
			}
			else
			{
				break;
			}
		}
		arr[j + 1] = ntemp;  //reason: j--
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
	int arr[10] = {9,3,5,7,1,8,0,4,2,0};
	printf("origin array:\n");
	OutPutArray(arr, 10);
	
	printf("insert sort result:\n");
	InsertSort(arr, 10);
	OutPutArray(arr, 10);
	return 0;
}