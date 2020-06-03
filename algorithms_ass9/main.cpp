// GROUP:   G4
// ID:      20150091
// Assign:  09
// Assign:  Knapsack
// UVA:     10130
// Name:    john alfy khalil
// UVA Username: Erouka

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Obj
{
    int v; // value (price) of object
    int w; // weight of object
};

Obj a[1000];

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T1[1001][31];

int Knapsack1(int n, int w)
{
    if(n==0)
    {
        T1[n][w]=0;
        return 0;
    }
    if(T1[n][w]>=0)
    {
        return T1[n][w];
    }
    T1[n][w]=Knapsack1(n-1,w);

    int cw=a[n-1].w;
    int  cv=a[n-1].v;
    if(cw<=w)
    {
        int r=cv+Knapsack1(n-1,w-cw);
        if(r>T1[n][w])
        {
            T1[n][w]=r;
        }
    }
    return T1[n][w];


}

int ComputeKnapsack1(int N, int W) // Recursive - memoization - initialize T then call Knapsack1(N,W);
{
    for(int i=0; i<1001; i++)
    {
        for(int y=0; y<31; y++)
        {
            T1[i][y]=-1;
        }

    }
    return Knapsack1(N,W);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T2[1001][31];

int ComputeKnapsack2(int N, int W)// Bottom-up, do not save space
{
    for(int n=0; n<=N; n++)
    {
        for(int w=0; w<=W; w++)
        {
            if(n==0)
            {
                T2[n][w]=0;
                continue;
            }
            T2[n][w]=T2[n-1][w];
            int cw=a[n-1].w;
            int cv=a[n-1].v;
            if(cw<=w)
            {
                int r=cv+T2[n-1][w-cw];
                if(r>T2[n][w])
                {
                    T2[n][w]=r;
                }
            }
        }
    }
    return T2[N][W];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T3[2][31];
int ComputeKnapsack3(int N, int W) // Bottom-up, use two rows only
{
    int cur=0;
    for(int n=0; n<=N; n++)
    {
        for(int w=0; w<=W; w++)
        {
            if(n==0)
            {
                T3[cur][w]=0;
                continue;
            }
            T3[cur][w]=T3[1-cur][w];
            int cw=a[n-1].w;
            int cv=a[n-1].v;
            if(cw<=w)
            {
                int r=cv+T3[1-cur][w-cw];
                if(r>T3[cur][w])
                {
                    T3[cur][w]=r;
                }
            }
        }
        cur=1-cur;
    }
    return T3[1-cur][W];
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T4[31];
int ComputeKnapsack4(int N, int W)// Bottom-up, save maximum space
{
    for(int n=0; n<=N; n++)
    {

        for(int w=W; w>=0; w--)
        {
            if(n==0)
            {
                T4[w]=0;
                continue;
            }

            int ret=T4[w];
            int cv=a[n-1].v;
            int cw=a[n-1].w;
            if(cw<=w)
            {
                int r=cv+T4[w-cw];
                if(r>ret)
                {
                    T4[w]=r;
                }
            }

        }
    }
    return T4[W];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Compute()
{
   // freopen("input.txt", "r", stdin);
    int familyN,Testcases,G,WG;
    cin>>Testcases;
    while(Testcases--)
    {
        cin>>familyN;
        for(int i=0 ; i<familyN ; i++)
        {
            cin>>a[i].v;
            cin>>a[i].w;
        }
        int maxValueOfGoods=0;
        cin>>G;
        while(G--)
        {
            cin>>WG;
            maxValueOfGoods+=ComputeKnapsack3( familyN, WG) ;
        }
        cout<<maxValueOfGoods<<endl;
    }

}
int main()
{

    Compute();

    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

