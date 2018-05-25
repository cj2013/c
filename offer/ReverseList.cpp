//反转单向链表和双向链表
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

struct DNode
{
	int		nValue;
	DNode*	pPre;
	DNode*	pNext;
	DNode()
	{
		pPre = nullptr;
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


DNode* CreateDNodeList(int* arr, int nLen)
{
	DNode* pHead = nullptr;
	DNode* p = nullptr;
	for (int i = 0; i < nLen; i++)
	{
		DNode* pNewNode = new DNode;
		pNewNode->nValue = arr[i];
		if (pHead == NULL)
		{
			pHead = pNewNode;
			p = pHead;
		}
		else
		{
			p->pNext = pNewNode;
			pNewNode->pPre = p;
			p = pNewNode;
		}
	}
	return pHead;
}

void OutPutDNode(DNode* pHead)
{
	DNode* p = pHead;
	while (p != nullptr)
	{
		printf("--%d", p->nValue);
		p = p->pNext;
	}
	printf("\n");
}

Node* ReverseNodeListStack(Node* pHead)
{
	stack<Node*> sk;
	Node* p = pHead;
	while (p != nullptr)
	{
		sk.push(p);
		p = p->pNext;
	}

	Node* pNew = nullptr;
	Node* q = nullptr;
	while(!sk.empty())
	{
		Node* pTemp = sk.top();
		sk.pop();
		pTemp->pNext = nullptr;
		if (pNew == nullptr)
		{
			pNew = pTemp;
			q = pTemp;
		}
		else
		{
			q->pNext = pTemp;
			q = pTemp;
		}
	}

	return pNew;
}

Node* ReverseNodeList(Node* pHead)
{
	if (pHead == nullptr || pHead->pNext == nullptr)
	{
		return pHead;
	}
	Node* p = pHead;
	pHead = nullptr;
	while (p)
	{
		Node* pNext = p->pNext;
		if (pHead == nullptr)
		{
			p->pNext = nullptr;
			pHead = p;
		}
		else
		{
			p->pNext = pHead;
			pHead = p;
		}
		p = pNext;
	}
	return pHead;
}

DNode* ReverseDNodeList(DNode* pHead)
{
	DNode* p = pHead;
	pHead = nullptr;
	while (p != nullptr)
	{
		DNode* r = p->pNext;
		if (pHead == nullptr)
		{
			p->pNext = nullptr;
			p->pPre = nullptr;
			pHead = p;
		}
		else
		{
			p->pNext = pHead;
			pHead->pPre = p;
			p->pPre = nullptr;
			pHead = p;
		}
		p = r;
	}
	return pHead;
}


int main()
{
	constexpr int COUNT = 10;
	int arr[COUNT];
	int arr2[COUNT];
	for (int i = 0; i < COUNT; i++)
	{
		arr[i] = i;
		arr2[i] = i * 10;
	}
	Node* pHead = CreateNodeList(arr, COUNT);
	printf("origin Node list:\n");
	OutPutNodeList(pHead);

	DNode* pDHead = CreateDNodeList(arr2, COUNT);
	printf("origin dNode list:\n");
	OutPutDNode(pDHead);

	Node* pRes = ReverseNodeList(pHead);
	printf("reverse origin Node list:\n");
	OutPutNodeList(pRes);

	DNode* pRes2 = ReverseDNodeList(pDHead);
	printf("reverse origin DNode list:\n");
	OutPutDNode(pRes2);

	return 0;
}