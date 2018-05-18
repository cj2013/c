//use two stack param to relalize a Queue function
#include <iostream>
#include <stack>
#include <cassert>
#include <cstdlib>
using namespace std;

class StackQueue
{
public:
    void Push(int nValue);  //add to tail
    void Pop();     //delete from front
    int Top();      //get front value
private:
    stack<int> m_popStack;
    stack<int> m_pushStack;
};

void StackQueue::Push(int nValue)
{
    m_pushStack.push(nValue);
}

void StackQueue::Pop()
{
    assert(!(m_popStack.empty() && m_pushStack.empty()));
    if(m_popStack.empty())
    {
        while(!m_pushStack.empty()){
            m_popStack.push(m_pushStack.top());
            m_pushStack.pop();
        }
    }
    m_popStack.pop();
}

int StackQueue::Top()
{
    assert(!(m_popStack.empty() && m_pushStack.empty()));
    if(m_popStack.empty())
    {
        while(!m_pushStack.empty())
        {
            m_popStack.push(m_pushStack.top());
            m_pushStack.pop();
        }
    }
    return m_popStack.top();
}


int main()
{
    StackQueue sq;
    sq.Push(2);
    sq.Push(6);
    cout << sq.Top() << endl;
    sq.Pop();

    sq.Push(5);
    cout << sq.Top() << endl;
    system("pause");
    return 0;
}
