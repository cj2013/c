//删除倒数第K个结点，单向列表/双向列表
#include <iostream>
#include <cstdlib>
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

Node* DeleteLastKNode(Node* pHead, int K)
{
	Node* p = pHead;
	int nCount = 0;
	while(p != nullptr)
	{
		nCount++;
		p = p->pNext;
	}

	//从前删除索引
	int nDelIndex = nCount - K ; //从0开始
	if (nDelIndex < 0 || nDelIndex > (nCount -1 ))
	{
		return pHead;
	}
	
	p = pHead;
	if (nDelIndex == 0)		//删除第一个
	{
		p = p->pNext;
		delete pHead;
		pHead = nullptr;
		return p;
	}

	for (int i = 0; i < nDelIndex - 1; i++)
	{
		p = p->pNext;
	}
	//删除P的下一个
	Node* pDelNode = p->pNext;
	if (pDelNode->pNext == nullptr)
	{
		p->pNext = nullptr;
		delete pDelNode;
		pDelNode = nullptr;
	}
	else
	{
		p->pNext = pDelNode->pNext;
		delete pDelNode;
		pDelNode = nullptr;
	}
	return pHead;
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

DNode* DeleteDNodeLastK(DNode* pHead, int K)
{
	if (pHead == nullptr || K < 0)
	{
		return pHead;
	}
	DNode* p = pHead;
	while (p->pNext != nullptr)
	{
		p = p->pNext;
	}

	if (K == 1)
	{
		if (p->pPre != nullptr)
		{
			p->pPre->pNext = nullptr;
			delete p;
			p= nullptr;
			return pHead;
		}
		else
		{
			return nullptr;
		}
	}

	DNode* pNext = p;
	for (int i = 1; i < K - 1; i++)
	{
		if (pNext != nullptr)
		{
			pNext = pNext->pPre;
		}
		else
		{
			return pHead;
		}
	}

	if (pNext->pPre != nullptr)
	{
		DNode* pDelNode = pNext->pPre;
		if (pDelNode->pPre == nullptr)
		{
			pHead = pDelNode->pNext;
			delete pDelNode;
			pDelNode = nullptr;
		}
		else
		{
			pDelNode->pPre->pNext = pNext;
			pNext->pPre = pDelNode->pPre;
			delete pDelNode;
			pDelNode = nullptr;
		}
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

	Node* pRes = DeleteLastKNode(pHead, 3);
	printf("node list after delete:\n");
	OutPutNodeList(pRes);
	

	DNode* pRes2 = DeleteDNodeLastK(pDHead, 3);
	printf("dnode list after delete:\n");
	OutPutDNode(pRes2);
	return 0;
}