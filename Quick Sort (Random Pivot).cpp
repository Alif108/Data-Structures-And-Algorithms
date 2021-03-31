#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void Swap(int &a,int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

int Partition(int a[],int start, int end)
{
    //int y = start + rand()%(end-start+1);
    int x = end;
    swap(a[start + rand()%(end-start+1)],a[x]);

    int pivot = a[x];

    int i = start-1;

    for(int j=start; j<=end-1; j++)
    {
        if(a[j]<=pivot)
        {
            i++;
            Swap(a[i],a[j]);
        }
    }

    Swap(a[i+1],a[end]);

    return i+1;
}

void QuickSort(int a[],int start, int end)              ///Worst Case: O(n^2)
{                                                       ///Average Case: O(n*logn)
    if(start<end)
    {
        int mid = Partition(a,start,end);
        QuickSort(a,start,mid-1);
        QuickSort(a,mid+1,end);
    }
}

int main()
{
    srand(time(NULL));
    int a[20];
    for(int i=0; i<20; i++)
    {
        a[i] = rand()%20;
        cout<<a[i]<<" ";
    }
    cout<<endl;
    QuickSort(a,0,19);
    for(int i=0; i<20; i++)
        cout<<a[i]<<" ";

    return 0;
}