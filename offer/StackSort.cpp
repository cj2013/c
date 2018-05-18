//use one stack sort another stack
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <stack>
using namespace std;

void sort(stack<int>& sk)
{
    if(sk.empty())
    {
        return;
    }

    stack<int> hpsk;
    int nV = sk.top();
    hpsk.push(nV);
    sk.pop();
    while(!sk.empty())
    {
        int curV = sk.top();
        sk.pop();
        while(!hpsk.empty() && hpsk.top() > curV)
        {
            sk.push(hpsk.top());
            hpsk.pop();
        }
        hpsk.push(curV);
    }

    while(!hpsk.empty())
    {
        sk.push(hpsk.top());
        hpsk.pop();
    }

}


int main()
{
    stack<int> sk;
    sk.push(1);
    sk.push(4);
    sk.push(2);
    sk.push(3);

    sort(sk);

    while(!sk.empty())
    {
        cout << sk.top() << endl;
        sk.pop();
    }
    return 0;
}
