// GROUP:   G_4
// ID:      20150091
// Assign:  10
// Assign:  MatChain
// UVA:     348
// Name1:   john alfy khalil
// UVA Username: Erouka

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////


int p[11]; // the dimensions of matrices

int T[11][11]; // T[a][b]=the optimal number of multiplication of p[a]...p[b]
int D[11][11]; // D[a][b]=the decision (value of k) that gets T[a][b]

// Top down version
int MatChain(int a, int b) // Recursive
{
    if(a+1==b)
    {
        T[a][b]=0;
        return 0;
    }
    if(T[a][b]>=0)
    {
        return T[a][b];
    }
    int k;
    T[a][b]=0X7FFFFFFF;
    for(int k=a+1; k<b; k++)
    {
        int v=MatChain(a,k)+MatChain(k, b)+p[a]*p[k]*p[b];
        if(v<T[a][b])
        {
            T[a][b]=v;
            D[a][b]=k;
        }
    }
    return T[a][b];
}
void MatChainTopDown(int n) // Initialize T then call MatChain(0,n)
{
    for(int i=0; i<11; i++)
    {
        for(int y=0; y<11; y++)
        {
            T[i][y]=-1;
        }
    }

    MatChain(0,n);
}
// BottomUp version

void MatChainBottomUp(int n)
{

    for(int i=0; i<11; i++)
    {
        for(int y=0; y<11; y++)
        {
            T[i][y]=-1;
        }
    }
    int j=0;
    for(int s=1; s<=n; s++)
    {
        for(int i=0; i+s<=n; i++)
        {
            j=i+s;
            if(i+1==j)
            {
                T[i][j]=0;
                continue;
            }
            int k;
            T[i][j]=0X7FFFFFFF;
            for(int k=i+1; k<j; k++)
            {
                int v=MatChain(i,k)+MatChain(k,j)+p[i]*p[k]*p[j];
                if(v<T[i][j])
                {
                    T[i][j]=v;
                    D[i][j]=k;
                }
            }
            //return T[i][j];

        }
    }


}

// Recursive to output the solution for both versions
void MatChainSol(int a, int b)
{
    if(a+1==b)
    {
        cout<<"A"<<b;
        return;
    }
    int k=D[a][b];
    cout<<"(";
    MatChainSol(a,k);
    cout<<" X ";
    MatChainSol(k,b);
    cout<<")";
}

void Compute()
{
    int N,Num1,Num2,COUNT=1;
    cin>>N;
    while(true)
    {
        if(N==0) break;
        for(int i=0 ; i<N ; i++)
        {
            cin>>Num1;
            cin>>Num2;
            p[i]=Num1;
            if(i==N-1)
            {
                i++;
                p[i]=Num2;
            }
        }
        //  MatChainTopDown(N);// Initialize T then call MatChain(0,n)
        MatChainTopDown(N);
        cout<<"Case "<<COUNT++<<": ";
        MatChainSol(0, N);
        cout<<endl;
        cin>>N;

    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    //freopen("input_assign10_00348.txt", "r", stdin);
    Compute();

    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

