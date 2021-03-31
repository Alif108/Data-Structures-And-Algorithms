#include <iostream>

using namespace std;


double frac(int W,int w[],int v[], int n)                       ///O(n) if ordered, else O(n*logn)
{
    double vw[n];           ///array for value per weight

    int m = n;              ///To keep count of the elements
    for(int i=0; i<n; i++)
    {
        vw[i] = v[i]/w[i];
    }

    double x;               ///fraction variable

    double sum = 0;

    while(W>0 && m>0)
    {
        int Max = -99;
        int MaxIdx = -99;

        for(int i=0; i<n; i++)
        {
            if(Max < vw[i])
            {
                Max = vw[i];
                MaxIdx = i;
                //cout<<Max<<" "<<MaxIdx<<endl;
            }
        }
        vw[MaxIdx] = -999;              ///making the previous max -999

        x = (double)W/w[MaxIdx];

        if(x > 1)
            x=1;

        sum += x*v[MaxIdx];
        W = W - x*w[MaxIdx];
        m--;                            ///decreasing no. of elements
    }
    return sum;
}

int main()
{
    int w[] = {10,20,30,25,35};
    int v[] = {60,100,120,50,70};
    int W = 60;

    cout<<frac(W,w,v,5)<<endl;

    return 0;
}
