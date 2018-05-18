//a stack hava the function of getMin
//time complexity o(1) space complexity o(1)
#include <iostream>
#include <stack>
#include <cassert>
#include <cstdlib>
using namespace std;

class MinStack
{
public:
    MinStack();
    ~MinStack();
    void Push(int nValue);
    void  Pop();
    int GetMin();
private:
    stack<int> m_Stack;
    stack<int> m_minStack;
};

MinStack::MinStack()
{

}

MinStack::~MinStack()
{

}

void MinStack::Push(int nValue)
{
    if(m_minStack.empty())
    {
        m_minStack.push(nValue);
    }
    else
    {
        if(m_minStack.top() > nValue)
        {
            m_minStack.pop();
            m_minStack.push(nValue);
        }
    }
    m_Stack.push(nValue);
}

void MinStack::Pop()
{
    assert(!m_Stack.empty());
    int nRes = m_Stack.top();
    if (nRes == m_minStack.top())
    {
        m_minStack.pop();
    }
    m_Stack.pop();
}

int MinStack::GetMin()
{
    if(m_minStack.empty()){
        return -1;
    }
    return m_minStack.top();
}

int main()
{
    MinStack tk1;
    for(int i = 5; i < 8; i++){
        tk1.Push(i);
    }
    cout << tk1.GetMin() << endl;
    system("pause");
    return 0;
}
