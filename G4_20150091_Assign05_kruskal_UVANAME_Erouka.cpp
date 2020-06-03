// GROUP:   G4
// ID:      20150091
// Assign:  05
// Assign:  Kruskal
// UVA:     11631
// Name:    Erouka

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <queue>
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
        for(int i=0; i<=n; i++)
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

struct Edge
{
	int u, v;
	int w;
};

template<class Type>
struct MergeSorter
{
    bool(*IsBefore) ( Type &a, Type &b);
    void initialize( bool(*__isBefore)(Type &,Type & ) )
    {
        IsBefore=(*__isBefore);
    }

    void Merge(Type* a, int n, bool (*IsBefore)(Type& a, Type& b))
    {
        int mid =(n/2);
        if(n<=1)
        {
            return ;
        }
        int i=0,j=mid,k;
        Type *t=new Type [n];
        for( k=0; k<n; k++)
        {
            if( j==n ||( i<mid && IsBefore( a[i], a[j])   ) )
            {
                t[k]=a[i++];
            }
            else
            {
                t[k]=a[j++];
            }
        }
        for(i=0; i<n; i++)
        {
            a[i]=t[i];
        }
        delete []t;
    };


    void MergeSort(Type* a, int n, bool (*IsBefore)(Type& a, Type& b))
    {
        int mid=n/2;
        if(n<=1)
        {
            return ;
        }
        MergeSort(a,mid,IsBefore);
        MergeSort(a+mid, n-mid,IsBefore ) ;
        Merge(a, n,IsBefore );
    };
};

bool IsBeforeEdge(Edge& a, Edge& b)
{
	return a.w<b.w;
}

int KruskalMsT (Edge * &List , int sz )
{
    DisjointSets s;
    s.Initialize(sz);
    int minweight=0;
    MergeSorter <Edge> v ;
    v.initialize(IsBeforeEdge);
    v.MergeSort(List,sz ,IsBeforeEdge);
    for(int i=0 ; i< sz ; i++)
    {
        if(s.Union(List[i].u , List[i].v))
        {
            minweight+=List[i].w;
        }

    }
return minweight;
}
int main()
{

Edge *p;
while(true)
{
    long long x , y;
    long long allcost=0;
    cin>>x;
    cin>>y;
    if(x==0 && y==0)
        return 0 ;
    p=new Edge [y];
    for(int i=0 ; i<y ; i++)
    {
        cin>>p[i].u;
        cin>>p[i].v;
        cin>>p[i].w;
        allcost+=p[i].w;
    }
    int i=KruskalMsT(p,y);
    cout<<allcost-i<<endl;

}


delete [] p;
	return 0;
}

