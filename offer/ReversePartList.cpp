//反转部分单向链表
#include <iostream>
#include <cstdlib>
#include <stack>
using namespace std;

struct Node
{
	int nValue;
	Node* pNext;
	Node()
	{
		pNext = nullptr;
	}
};

Node* CreateNodeList(int* arr, int nLen)
{
	Node* pHead = nullptr;
	Node* p = nullptr;
	for (int i = 0; i < nLen; i++)
	{
		Node* pNewNode = new Node;
		pNewNode->nValue = arr[i];
		if (pHead == nullptr)
		{
			pHead = pNewNode;
			p = pHead;
		}
		else
		{
			p->pNext = pNewNode;
			p = p->pNext;
		}
	}
	return pHead;
}

void OutPutNodeList(Node* pHead)
{
	Node* p = pHead;
	while (p != nullptr)
	{
		printf("--%d", p->nValue);
		p = p->pNext;
	}
	printf("\n");
}

Node* ReversePartList(Node* pHead, int nBegin, int nEnd)
{
	Node* pBegin = nullptr;
	Node* pEnd = nullptr;
	Node* p = pHead;
	
	if (nBegin == 1)
	{
		//后端部分起点
		for (int i = 0; i <= nEnd - nBegin; i++)
		{
			if (p != nullptr)
			{
				p = p->pNext;
			}
		}
		if(p != nullptr)
		{
			pBegin = p->pNext;
		}

		//前端逆序
		Node* pp = pHead;
		p = pHead;
		pHead = nullptr;
		for(int i = 0; i <= nEnd - nBegin; i++)
		{
			Node* pNext = p->pNext;
			if (pHead == nullptr)
			{
				pHead = p;
				pHead->pNext = nullptr;
			}
			else
			{
				p->pNext = pHead;
				pHead = p;
			}
			p = pNext;
		}
		//组合
		pp->pNext = p;
	}
	else
	{
		Node* pOrgEnd = pHead;  //前端部分终点
		for (int i = 0; i < nBegin -2; i++)
		{
			if(pOrgEnd != nullptr)
			{
				pOrgEnd = pOrgEnd->pNext;
			}
		}

		Node* pOrgStart2 = pOrgEnd;		//后端部分起点
		for (int i = 0; i <= nEnd - nBegin + 1; i++)
		{
			if (pOrgStart2 != nullptr)
			{
				pOrgStart2 = pOrgStart2->pNext;
			}
		}


		//中间逆序
		Node* pCur = pOrgEnd->pNext;
		Node* pPre = nullptr;
		Node* pSmallHead = pCur;
		printf("pSmallHead:%d\n", pSmallHead->nValue);
		for (int i = 0; i <= nEnd - nBegin; i++)
		{
			Node* pNext = pCur->pNext;
			if (i == 0)
			{
				pCur->pNext = nullptr;
				pPre = pCur;
			}
			else
			{
				pCur->pNext = pPre;
				pPre = pCur;
			}
			if (i < nEnd - nBegin)
			{
				pCur = pNext;
			}
		}
		//重组
		//pCur为最后一个
		pOrgEnd->pNext = pCur;
		printf("orgintend:%d\n", pOrgEnd->nValue);
		printf("pCur:%d\n", pCur->nValue);
		pSmallHead->pNext = pOrgStart2;
	}
	return pHead;
}


int main()
{
	constexpr int COUNT = 10;
	int arr[COUNT];
	for (int i = 0; i < COUNT; i++)
	{
		arr[i] = i;
	}
	Node* pHead = CreateNodeList(arr, COUNT);
	printf("origin Node list:\n");
	OutPutNodeList(pHead);

	Node* pRes = ReversePartList(pHead, 1, 4);
	printf("reverse part origin Node list:\n");
	OutPutNodeList(pRes);

	return 0;
}