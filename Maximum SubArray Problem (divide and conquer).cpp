#include <iostream>
#include <cstdlib>
#include <ctime>
#define min -99999

using namespace std;

int max(int a,int b)
{
    if(a>b)
        return a;
    else return b;
}

int Max_Subarray(int a[],int n)
{
    if(n==1)
        return a[0];

    int m = n/2;

    //int left_mss = Max_Subarray(a,m);
    //int right_mss = Max_Subarray(a+m,n-m);

    int left_sum = min;
    int right_sum = min;
    int sum = 0;

    for(int i=m; i<n; i++)
    {
        sum += a[i];
        right_sum = max(right_sum,sum);
    }

    sum = 0;

    for(int i=m-1; i>=0; i--)
    {
        sum += a[i];
        left_sum = max(left_sum,sum);
    }
    int ans = max(left_sum,right_sum);

    return max(ans,left_sum+right_sum);
}

int main()
{
    int n;
    cin>>n;
    int a[n];

    for(int i=0; i<n; i++)
        cin>>a[i];

    cout<<Max_Subarray(a,n);

    return 0;
}
