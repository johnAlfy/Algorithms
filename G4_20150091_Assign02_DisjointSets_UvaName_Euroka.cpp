// GROUP:   G4
// ID:      20150091
// Assign:  02
// Assign:  DisjointSets
// UVA:     10608
// Name:    Euroka

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

struct DisjointSets
{
    int n;
    int* parent;
    int *num_nodes;

    void Initialize(int _n)
    {
        n=_n;
        parent=new int[n];
        num_nodes=new int [n];
        for(int i=1; i<=n; i++)
        {
            num_nodes[i]=1;
            parent[i]=i;
        }


    };
    void Destroy()
    {
        delete parent;
        delete num_nodes;
    };
    int Find(int i)
    {
        if(parent[i]==i)
        {
            return i;
        }
        return Find(parent[i]);


    };
    bool Union(int i, int j)
    {
        int x=Find(i);
        int y=Find(j);

        if(x==y)
        {
            return false;
        }
        else
        {
            if(num_nodes[x]>=num_nodes[y])
            {
                parent[y]=x;
                num_nodes[x]+=num_nodes[y];
            }
            else
            {
                parent[x]=y;
                num_nodes[y]+=num_nodes[x];
            }
            return true;
        }

    };
};

int main()
{
    DisjointSets d ;

    int testcases ;
    cin >>testcases;
    while(testcases--)
    {
        int n, m;
        cin >> n;
        d.Initialize(n);
        cin >> m;
        for(int i=0 ; i < m ; i++)
        {
            int a, b;
            cin >> a ;
            cin >> b ;
            d.Union(a,b);
        }
        int maX=d.num_nodes[1];
        for (int i=1 ; i <= d.n ; i++)
        {
            if(d.num_nodes[i] > maX)
            {
                maX=d.num_nodes[i];
            }
        }
        cout<<maX<<endl;

    }

    d.Destroy();

    return 0;
}
