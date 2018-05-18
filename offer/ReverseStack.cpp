//
#include <iostream>
#include <cstdlib>
#include <stack>
#include <cassert>
using namespace std;

int getAndRemoveTop(stack<int>& sk)
{
    assert(!sk.empty());
    int nTop = sk.top();
    sk.pop();
    if(sk.empty())
    {
        return nTop;
    }
    else
    {
        int nLast = getAndRemoveTop(sk);
        sk.push(nTop);
        return nLast;
    }

}

void reverse(stack<int>& sk)
{
    if(sk.empty())
    {
        return;
    }

    int nTop = getAndRemoveTop(sk);
    reverse(sk);
    sk.push(nTop);
}

int main()
{
    stack<int> sk;

    for(int i = 0; i < 5; i++)
    {
        sk.push(i);
    }

    reverse(sk);

    while(!sk.empty())
    {
        cout << sk.top() << endl;
        sk.pop();
    }

    system("pause");
    return 0;
}
