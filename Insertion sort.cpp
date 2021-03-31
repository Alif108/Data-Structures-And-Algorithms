#include <iostream>
#include <cstdlib>

using namespace std;

void insertion(int a[], int n)
{
    int value;
    int hole;
    for(int i=1; i<n ;i++)
    {
        hole = i;
        value = a[i];
        while(hole>0 && a[hole-1]>value)
        {
            a[hole] = a[hole-1];
            hole--;
        }
        a[hole] = value;
    }
}

int main()
{
    int a[10];
    for(int i=0; i<10; i++)
    {
        a[i] = rand()%30;
        cout<<a[i]<<" ";
    }
    cout<<endl<<endl;

    insertion(a,10);

    for(int i=0; i<10 ;i++)
    {
        cout<<a[i]<<" ";
    }
    return 0;
}
