#include <iostream>
#include <cstdlib>
#include <vector>
#include <stack>
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
    void AddToHead(int nValue);
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

void CList::AddToHead(int nValue)
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
    pNode->pNext = m_pHead;
    m_pHead = pNode;
}

void CList::TP()
{
    ListNode* pHead = m_pHead;
    while (pHead != NULL) {
        cout << "--" << pHead->nValue ;
        pHead = pHead->pNext;
    }
    cout << endl;
}

int ListToValue(ListNode* pHead)
{
    if(pHead == NULL)
    {
        return 0;
    }
    int nV = 0;
    ListNode* pTemp = pHead;
    while(pTemp != NULL)
    {
        nV = nV * 10 + pTemp->nValue;
        pTemp = pTemp->pNext;
    }
    return nV;
}


int CalcListAddValue(CList* pA, CList* pB)
{
    int nA = ListToValue(pA->m_pHead);
    int nB = ListToValue(pB->m_pHead);
    int nRes = nA + nB;
    return nRes;
}

int main()
{
    // 901 + 123 = 1024
    CList lA, lB;
    lA.Add(9);
    lA.Add(0);
    lA.Add(1);
    lB.Add(1);
    lB.Add(2);
    lB.Add(3);

    int nValue = CalcListAddValue(&lA, &lB);
    CList lC;
    while(nValue != 0)
    {
        int v = nValue % 10;
        lC.AddToHead(v);
        nValue = int(nValue / 10);
    }
    lA.TP();
    lB.TP();
    lC.TP();
    system("pause");
    return 0;
}
