#include <iostream>         ///...Memoization
#define length 10000

using namespace std;

int F[length];

void init()
{
    for(int i=0; i<length; i++)
        F[i] = -1;

    F[0] = 1;
    F[1] = 1;
}

unsigned int Fibonacci(int n)
{
    if(F[n] == -1)
        F[n] = Fibonacci(n-1) + Fibonacci(n-2);

    return F[n];
}
int main()
{
    init();
    unsigned int x;
    cout<<"Enter your number: ";
    cin>>x;
    cout<<Fibonacci(x)<<endl;
}

