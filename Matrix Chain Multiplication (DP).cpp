#include <iostream>

using namespace std;

void printParenth(int *s,int n,int i,int j,char &name)
{
    if(i == j)
    {
        cout<<name;
        name++;
    }

    else
    {
        cout<<"(";
        printParenth(s,n,i,*((s+i*n)+j),name);
        printParenth(s,n,*((s+i*n)+j)+1,j,name);
        cout<<")";
    }
}

void Matrix_Chain(int d[],int p)
{
    int n = p;
    int q,j;
    int Min;

    int m[n][n];
    int s[n][n];

    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
    {
        m[i][j] = 0;
        s[i][j] = 0;
    }

    //for(int i=0; i<n; i++)
      //  m[i][i] = 0;

    for(int l = 1; l<n-1; l++)                 ///counting the difference between i and j for each iteration
    {
        for(int i=1; i<n-l; i++)
        {
            j = i+l;
            Min = 99999;

            for(int k=i; k<j; k++)
            {
                q = m[i][k] + m[k+1][j] + d[i-1]*d[k]*d[j];

                if(q<Min)
                {
                    Min = q;
                    s[i][j] = k;
                }
            }
            m[i][j] = Min;
        }
    }

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
            cout<<m[i][j]<<" ";
        cout<<endl;
    }

    cout<<endl;

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
            cout<<s[i][j]<<" ";
        cout<<endl;
    }

    cout<<endl;
    cout<<"Minimum multiplication is: "<<m[1][n-1]<<endl;

    char name = 'A';

    printParenth((int*)s,n,1,n-1,name);
}

int main()
{
    int d[] = {5,10,3,12};

    Matrix_Chain(d,4);
}
