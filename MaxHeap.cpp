#include <iostream>

using namespace std;

void Swap(int &x,int &y)
{
    int temp = x;
    x = y;
    y = temp;
}

class MaxHeap
{
    int *arr;
    int size;
    int capacity;

public:
    MaxHeap()
    {
        capacity = 10;
        arr = new int[capacity];
        size = -1;
    }

    int LeftChildIndex(int i)
    {
        return 2*i+1;
    }

    int RightChildIndex(int i)
    {
        return 2*i + 2;
    }

    int ParentIndex(int i)
    {
        return (i-1)/2;
    }

    void increaseCapacity()
    {
        capacity = 2*capacity;

        int *tempArray = new int[capacity];

        for(int i=0; i<size; i++)
        {
            tempArray[i] = arr[i];
        }

        delete arr;
        arr = tempArray;
    }

    void Insert(int x)
    {
        size++;

        if(size>capacity)
            increaseCapacity();

        arr[size] = x;

        int i = size;

        while(i>0 && arr[ParentIndex(i)]<arr[i])
        {
            Swap(arr[ParentIndex(i)],arr[i]);
            i = ParentIndex(i);
        }
    }

    void Heapify(int i)                             ///O(logn)
    {
        int left = LeftChildIndex(i);
        int right = RightChildIndex(i);

        int largest = i;

        if(arr[left] > arr[largest])
            largest = left;

        if(arr[right] > arr[largest])
            largest = right;

        if(largest != i)
        {
            Swap(arr[i],arr[largest]);
            Heapify(largest);
        }
    }

    int ExtractMax()
    {
        int Max = arr[0];

        arr[0] = arr[size];

        size--;

        Heapify(0);

        return Max;
    }

    void BuildHeap(int *a,int length)               ///O(n)
    {
        size = length;
        capacity = length;

        delete arr;
        arr = a;

        for(int i=length/2; i>=0; i--)
            Heapify(i);
    }

    void HeapSort()                             ///O(n*logn)
    {
        for(int i=size-1; i>=0; i--)
        //for(int i=size-1; j>=1; j--)
        {
            //cout<<arr[0]<<" ";
            Swap(arr[0],arr[i]);
            //cout<<arr[i]<<" ";
            //size--;
            Heapify(0);
        }
    }

    void Display()
    {
        for(int i=0 ;i<=size; i++)
            cout<<arr[i]<<" ";
    }

    int Min()
    {
        int length = size;
        int m = 9999999;
        for(int i=length/2; i<size; i++)
        {
            if(arr[i]<m)
                m = arr[i];
        }
        return m;
    }
};

int main()
{
    MaxHeap A;

    A.Insert(4);
    A.Insert(3);
    A.Insert(5);
    A.Insert(8);
    A.Insert(10);
    A.Insert(6);
    A.Insert(9);
    //cout<<A.ExtractMax()<<endl;

    //A.HeapSort();

    A.Display();
    cout<<endl<<A.Min()<<endl;
}
