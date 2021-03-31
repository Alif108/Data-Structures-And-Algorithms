#include <iostream>

using namespace std;

int Max(int a,int b)
{
    if(a>b)
        return a;
    else return b;
}

void Knap(int v[],int w[],int n,int W)                      ///O(n*W)
{
    int P[n+1][W+1];
    int Items[n];

    for(int i=0; i<n; i++)
        Items[i] = 0;

    for(int i=0; i<=n; i++)
        P[i][0] = 0;
    for(int i=0; i<=W ;i++)
        P[0][i] = 0;

    for(int i=1; i<=n; i++)
        for(int j=1; j<=W; j++)
    {
        if(j >= w[i-1])
            P[i][j] = Max(P[i-1][j],(P[i-1][j-w[i-1]])+v[i-1]);
        else
            P[i][j] = P[i-1][j];

    }

    for(int i=0; i<=n; i++)
    {
        for(int j=0; j<=W; j++)
            cout<<P[i][j]<<" ";
        cout<<endl;
    }

    int maxProfit = P[n][W];
    int i = n;
    int j = W;
    int x = maxProfit;

    while(x>0)
    {
        while(P[i][j-1] == x)
            j--;
        while(P[i-1][j] == x)
            i--;

        Items[i-1] = 1;
        x = x - v[i-1];

        for(int k=i; k>0; k--)
            for(int l=j-1; l>0; l--)
        {
            if(P[k][l] == x)
            {
                i = k;
                j = l;
                break;
            }
        }
    }
    for(int i=0; i<n; i++)
        cout<<Items[i]<<" ";
    cout<<endl;
    cout<<"Max Profit: "<<maxProfit;

}

int main()
{
    int w[] = {2,1,2,2,2};
    int v[] = {7,8,12,6,10};
    int W = 6;

    Knap(v,w,5,W);
}
