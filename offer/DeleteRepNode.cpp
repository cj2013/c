//delete repeat node of a link
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

class CList
{
public:
	CList();
	~CList();
	void Add(int nValue);
	void Output();
public:
	Node*  m_pHead;
};

CList::CList()
{
	m_pHead = NULL;
}

CList::~CList()
{
	Node* pCur = m_pHead;
	Node* pNext = pCur->pNext;
	while(pCur != NULL)
	{
		delete pCur;
		pCur = NULL;
		pCur = pNext;
		if(pNext != NULL)
		{
			pNext = pNext->pNext;
		}
	}
}

void CList::Add(int nValue)
{
	if(m_pHead == NULL)
	{
		m_pHead = new Node;
		m_pHead->nValue = nValue;
		return;
	}
	Node* pNode = m_pHead;
	while(pNode->pNext != NULL)
	{
		pNode = pNode->pNext;
	}
	Node* pNewNode = new Node;
	pNewNode->nValue = nValue;
	pNewNode->pNext = NULL;
	pNode->pNext = pNewNode;
}

void CList::Output()
{
	Node* pNode = m_pHead;
	while(pNode != NULL)
	{
		printf("--%d", pNode->nValue);
		pNode = pNode->pNext;
	}
	printf("\n");
}

void CreateList(int* arr, int nLen, CList& ls)
{
	for(int i = 0; i < nLen; i++)
	{
		ls.Add(arr[i]);
	}
}

Node* DeleteRepaetNode(Node* pHead)
{
	if(pHead == NULL || pHead->pNext == NULL)
	{
		return pHead;
	}
	Node* p = pHead;
	while (p != NULL)
	{
		Node* pre = p;
		Node* q = p->pNext;
		while(pre != NULL && q != NULL)
		{
			if(q->nValue == p->nValue)
			{
				pre->pNext = q->pNext;
				delete q; 
				q = NULL;
				q = pre->pNext;
			}
			else
			{
				pre = pre->pNext;
				q = q->pNext;
			}
		}
		p = p->pNext;
	}
	return pHead;

}

int main()
{
	int arr[11] = {1,2,3,4,4,3,2,1,1,2, 5};
	CList ls;
	CreateList(arr, 11, ls);
	ls.Output();

	Node* pNode = DeleteRepaetNode(ls.m_pHead);

	while(pNode != NULL)
	{
		printf("--%d", pNode->nValue);
		pNode = pNode->pNext;
	}
}