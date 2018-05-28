#include <iostream>
#include <cstdlib>
#include <stdio.h>
using namespace std;


//大数下沉，从小到大排序
void Bubble1(int* arr, int nCount)
{
	for(int i = 0; i < nCount; i++)
	{
		for(int j = 0; j < nCount - 1 - i; j++)
		{
			if(arr[j] > arr[j + 1])
			{
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

//小数上升，从小到大
void Bubble2(int* arr, int nCount)
{
	for(int i = 0; i < nCount; i++)
	{
		for(int j = nCount - 1; j >= i + 1; j--)
		{
			if(arr[j] < arr[j - 1])
			{
				int temp = arr[j];
				arr[j] = arr[j - 1];
				arr[j - 1] = temp;
			}
		}
	}
}

void Bubble2Optimize(int* arr, int nCount)
{
	bool bFlag= true;
	for(int i = 0; i < nCount && bFlag; i++)
	{
		bFlag = false;
		for(int j = nCount - 1; j >= i + 1; j--)
		{
			if(arr[j] < arr[j - 1])
			{
				int temp = arr[j];
				arr[j] = arr[j - 1];
				arr[j - 1] = temp;
				bFlag = true;
			}
		}
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
	
	printf("big value sink:\n");
	Bubble1(arr, 10);
	OutPutArray(arr, 10);
	
	int arr1[10] = {9,3,5,7,1,8,6,4,2,0};
	printf("small value rise:\n");
	Bubble2(arr1, 10);
	OutPutArray(arr1, 10);
	
	int arr2[10] = {9,3,5,7,1,8,6,4,2,0};
	printf("small value rise optimize:\n");
	Bubble2Optimize(arr2, 10);
	OutPutArray(arr2, 10);
	return 0;
}