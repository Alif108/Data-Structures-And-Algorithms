#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int Maximum(int a[],int n,int i,int j)          /// Time Complexity: O(n)
{
    int Max;

    if(i==j)
        Max = a[i];

    else if(i == j-1)
    {
        if(a[i]>a[j])
        {
            Max = a[i];
        }
        else
        {
            Max = a[j];
        }
    }

    else
    {
        int mid = (i+j)/2;

        int Fmax = Maximum(a,n,i,mid);
        int Gmax = Maximum(a,n,mid+1,j);

        if(Fmax>Gmax)
            Max = Fmax;
        else
            Max = Gmax;
    }
    return Max;
}

int main()
{
    srand(time(NULL));
    int n;
    cout<<"Size of the array: ";
    cin>>n;
    int a[n];
    cout<<"Enter array elements: "<<endl;
    for(int i=0; i<n; i++)
    {
        a[i] = rand()%20;
        cout<<a[i]<<" ";
    }
    cout<<endl;

    cout<<Maximum(a,n,0,n-1)<<endl;

    return 0;
}
