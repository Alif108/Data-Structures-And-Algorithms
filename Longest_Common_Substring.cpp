#include <iostream>
#include <cstring>

using namespace std;

class LCS
{
    char X[100];
    char Y[100];
    int **c;
    int m;
    int n;

public:
    LCS(char *X1,char *Y1)
    {
        m = strlen(X1);
        n = strlen(Y1);

        for(int i=0; i<m; i++)
        {
            X[i] = X1[i];
        }
        for(int i=0; i<n; i++)
        {
            Y[i] = Y1[i];
        }
    }

    int maximum(int x,int y)
    {
        if(x>y)
            return x;
        else return y;
    }

    int LCS_LENGTH()
    {
        c = new int*[m+1];
        for(int i = 0; i < (m+1); i++)
        {
            c[i] = new int[n+1];
        }

        for(int i=0; i<=m; i++)
        {
            for(int j=0; j<=n; j++)
            {
                if(i==0 || j==0)
                    c[i][j] = 0;

                else if(X[i-1] == Y[j-1])
                {
                    c[i][j] = 1 + c[i-1][j-1];

                }
                else
                {
                    c[i][j] = maximum(c[i-1][j],c[i][j-1]);
                }
            }
        }
        return c[m][n];
    }

    void PRINT_LCS()
    {
        int idx = LCS_LENGTH();

        char b[idx+1];
        b[idx] = '\0';

        int i = m;
        int j = n;

        while(i>0 && j>0)
        {
            if(X[i-1] == Y[j-1])
            {
                b[idx-1] = X[i-1];
                i--;
                j--;
                idx--;
            }
            else if(c[i-1][j]>c[i][j-1])
                i--;
            else j--;
        }
    cout<<b;
    }
};

int main()
{
    char s1[100];
    char s2[100];

    cout<<"First String: ";
    cin>>s1;
    cout<<"Second String: ";
    cin>>s2;

    LCS ob(s1,s2);
    //cout<<ob.LCS_LENGTH()<<endl;
    ob.PRINT_LCS();
    return 0;
}
