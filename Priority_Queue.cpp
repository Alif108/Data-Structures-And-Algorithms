#include <iostream>
#define NULL_VALUE -99999

using namespace std;

class MaxHeap
{
    int size;
    int capacity;
    int *items;

public:
    MaxHeap()
    {
        size = 1;
        capacity = 10;
        items = new int[capacity];
        items[0] = size;
    }

    int getLeftChildIndex(int parentIndex)
    {
        return 2*parentIndex;
    }

    int getRightChildIndex(int parentIndex)
    {
        return 2*parentIndex + 1;
    }

    int getParentIndex(int childIndex)
    {
        return childIndex/2;
    }

    bool hasLeftChild(int parentIndex)
    {
        if(getLeftChildIndex(parentIndex) < size)
            return true;
        else return false;
    }

    bool hasRightChild(int parentIndex)
    {
        if(getRightChildIndex(parentIndex) < size)
            return true;
        else return false;
    }

    bool hasParent(int childIndex)
    {
        if(getParentIndex(childIndex) >= 1)
            return true;
        else return false;
    }

    int getLeftChild(int parentIndex)
    {
        return items[getLeftChildIndex(parentIndex)];
    }

    int getRightChild(int parentIndex)
    {
        return items[getRightChildIndex(parentIndex)];
    }

    int getParent(int childIndex)
    {
        return items[getParentIndex(childIndex)];
    }

    void swap(int idx1, int idx2)
    {
        int temp = items[idx1];
        items[idx1] = items[idx2];
        items[idx2] = temp;
    }

    void increaseCapacity()
    {
            capacity = capacity*2;
            int *tempItems = new int[capacity];
            for(int i=0; i<size; i++)
            {
                tempItems[i] = items[i];
            }
            delete items;
            items = tempItems;
    }

    int findMax()
    {
        if(size==1)
            return NULL_VALUE;
        else
            return items[1];
    }

    void heapifyUp()
    {
        int idx = size-1;
        while(hasParent(idx))
        {
            if(getParent(idx)<items[idx])
                swap(getParentIndex(idx),idx);
            idx = getParentIndex(idx);
        }
    }

    void heapifyDown()
    {
        int idx = 1;
        while(hasLeftChild(idx))
        {
            int largerChildIndex = getLeftChildIndex(idx);
            if(hasRightChild(idx) && getRightChild(idx)>getLeftChild(idx))
                largerChildIndex = getRightChildIndex(idx);

            if(items[idx]>items[largerChildIndex])
                break;
            else
            {
                swap(idx,largerChildIndex);
            }
            idx = largerChildIndex;
        }
    }

    int extractMax()
    {
        if(size==1)
            return NULL_VALUE;
        else
        {
            int item = items[1];
            swap(1,size-1);
            size--;
            heapifyDown();
            items[0] = size;
            return item;
        }
    }

    void insertItems(int a)
    {
        if(size==capacity)
            increaseCapacity();
        items[size] = a;
        size++;
        heapifyUp();
        items[0] = size;
    }
    void print()
    {
        for(int i=1; i<size; i++)
            cout<<items[i]<<endl;
    }

    void increaseKey(int i,int newKey)
    {
        items[i] = newKey;
        heapifyUp();
    }

    void decreaseKey(int i,int newKey)
    {
        items[i] = newKey;
        heapifyDown();
    }

    bool isEmpty()
    {
        if (size==1)
            return true;
        else return false;
    }

};

int main()
{
    MaxHeap H;
    int n;
    while(1)
    {
        cout<<"1.Insert"<<endl;
        cout<<"2.Find Max"<<endl;
        cout<<"3.Extract Max"<<endl;
        cout<<"4.Increase Key"<<endl;
        cout<<"5.Decrease Key"<<endl;
        cout<<"6.Print"<<endl;
        cout<<"7.Exit"<<endl;

        cin>>n;

        if(n==1)
        {
            int a;
            cout<<"Insert: ";
            cin>>a;
            H.insertItems(a);
        }
        else if(n==2)
        {
            cout<<H.findMax()<<endl;
        }
        else if(n==3)
        {
            cout<<H.extractMax()<<endl;
        }
        else if(n==4)
        {
            int pos;
            cout<<"Enter index: ";
            cin>>pos;
            int key;
            cout<<"Enter key: ";
            cin>>key;
            H.increaseKey(pos,key);
        }
        else if(n==5)
        {
            int pos;
            cout<<"Enter index: ";
            cin>>pos;
            int key;
            cout<<"Enter key: ";
            cin>>key;
            H.decreaseKey(pos,key);
        }
        else if(n==6)
        {
            H.print();
        }
        else if(n==7)
        {
            break;
        }
        else
        {
            cout<<"No Valid Action"<<endl;
        }
    }
    return 0;
}



