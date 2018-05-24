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

Node* ReverseNode(Node* pHead, int nLen, int nCount)
{
	if(nLen < nCount)
	{
		return pHead;
	}

    Node* pNew = NULL;
	Node* pNewTail = pHead;
	Node* p = pHead;
	Node* q = NULL;
	
	stack<Node*> sk;
	int nSize = 0;
	 
	while(p != NULL)
	{
		q = p->pNext;
		sk.push(p);
		nSize++;

		if(nSize == nCount)
		{
			while(!sk.empty())
			{
				Node* pCur = sk.top();
				pCur->pNext = NULL;
				sk.pop();
				if(pNew == NULL)
				{
					pNewTail = pCur;
					pNew = pNewTail;
				}
				else
				{
					pNewTail->pNext = pCur;
					pNewTail = pCur;
				}
			}
			pNewTail->pNext = q;
			nSize = 0;
		}
		p = q;
	}

	return pNew;
}


int main()
{
    int arr[] = {1,2,3,4,5,6,7,8,9,10,11};
    CList ls;
    CreateList(arr, 11, ls);
    ls.Output();

    Node* pNew = ReverseNode(ls.m_pHead, 11, 3);

    while(pNew != NULL)
    {
		printf("--%d", pNew->nValue);
        pNew = pNew->pNext;
    }
    printf("\n");
}
