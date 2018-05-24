//删除特定值结点
#include <iostream>
#include <cstdlib>
#include <stack>
#include <stdio.h>
using namespace std;

struct Node
{
	int nValue;
	Node* pNext;
	Node()
	{
		pNext = NULL;
	}
};


Node* CreatNodeArray(int* arr, int nLen)
{
	Node* pNode = NULL;
	for(int i = 0; i < nLen; i++)
	{
		Node* pNewNode = new Node;
		pNewNode->nValue = arr[i];
		pNewNode->pNext = NULL;
		if (pNode == NULL)
		{
			pNode = pNewNode;
		}
		else
		{
			Node* p = pNode;
			while(p->pNext != NULL)
			{
				p = p->pNext;
			}
			p->pNext = pNewNode;
		}
	}
	return pNode;
}

Node* DeleteNode(Node* pHead, int nValue)
{
	if(pHead == NULL)
	{
		return pHead;
	}
	//先删除头之后的重复元素，再处理头
	Node* pPre = pHead;
	Node* p = pHead->pNext;
	while (p != NULL)
	{
		if (p->nValue == nValue)
		{
			pPre->pNext = p->pNext;
			delete p; 
			p = NULL;
			p = pPre->pNext;
		}
		else
		{
			p = p->pNext;
			pPre = pPre->pNext;
		}
	}

	//处理头
	if (pHead->nValue == nValue)
	{
		Node* pTemp= pHead;
		pHead = pHead->pNext;
		delete pTemp;
		pTemp = NULL;
	}
	return pHead;
}

void OutPutNodeList(Node* pHead)
{
	Node* p = pHead;
	while(p != NULL)
	{
		printf("--%d", p->nValue);
		p = p->pNext;
	}
}

int main()
{
	int arr[11] = {1,2,3,4,4,3,2,1,1,2, 5};

	Node* pNode = CreatNodeArray(arr, 11);
	OutPutNodeList(pNode);
	printf("\n");

	Node* pRes = DeleteNode(pNode, 1);
	OutPutNodeList(pRes);

	system("pause");
	return 0;
}