//
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

struct ListNode
{
    ListNode*   pNext;
    int         nValue;
    ListNode()
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
    void TP();
public:
    ListNode* m_pHead;
};

CList::CList()
{
    m_pHead = NULL;
}

CList::~CList()
{
    if(m_pHead == NULL)
    {
        return;
    }

    ListNode* pHead = m_pHead;
    while(pHead != NULL)
    {
        ListNode* pNext = pHead->pNext;
        delete pHead;
        pHead = NULL;
        pHead = pNext;
    }
    m_pHead = NULL;
}
void CList::TP()
{
    ListNode* pHead = m_pHead;
    while (pHead != NULL) {
        cout << pHead->nValue << endl;
        pHead = pHead->pNext;
    }
}

void CList::Add(int nValue)
{
    ListNode* pNode = new ListNode;
    pNode->nValue = nValue;
    ListNode* pHead = m_pHead;
    if(pHead == NULL)
    {
        pHead = pNode;
        m_pHead = pHead;
        return;
    }
    while(pHead->pNext != NULL)
    {
        pHead = pHead->pNext;
    }
    pHead->pNext = pNode;
}

void GetConjunctVector(vector<int>& vecConjunct, ListNode* pHeadA, ListNode* pHeadB)
{
    ListNode* pA = pHeadA;
    ListNode* pB = pHeadB;
    while(pA != NULL && pB != NULL)
    {
        if(pA->nValue == pB->nValue)
        {
            vecConjunct.push_back(pA->nValue);
            pA = pA->pNext;
            pB = pB->pNext;
        }
        else if(pA->nValue < pB->nValue)
        {
            pA = pA->pNext;
        }
        else
        {
             pB = pB->pNext;
        }
    }
}

int main()
{
    CList lA;
    CList lB;
    for(int i = 0; i < 10; i++)
    {
        lA.Add(i * 2);
        lB.Add(i * 4);
    }

    vector<int> vec;
    GetConjunctVector(vec, lA.m_pHead, lB.m_pHead);
    int nSize = (int)vec.size();
    for(int i = 0; i < nSize; i++)
    {
        cout << vec[i] << endl;
    }
    return 0;
}
