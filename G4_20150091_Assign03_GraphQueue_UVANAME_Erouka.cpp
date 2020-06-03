// GROUP:   G4
// ID:      20150091
// Assign:  03
// Assign:  Graphs
// UVA:     924
// Name:    Erouka


#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>

using namespace std;

template<class value>
struct Array
{
value *arr;
int n, Size;
void initialize()
{
    Size=1;
    n=0;
    arr=new value [Size];
}
void destroy()
{
    delete [] arr ;
}
value& operator[](int i)
{
    return arr[i];
}
void addLast(value v)
{
    if(n==Size)
    {
        Size*=2;
        value * New_arr=new value[Size];
        for(int i=0 ; i<n ; i++)
        {
            New_arr[i]=arr[i];
        }
        delete [] arr;
        arr=New_arr;

    }
        arr[n++]=v;
}
void removeLast()
{
    if(n==0)
        return;
    n--;
}
int SIZE ()
{
        if(n>=0)
            return n;
        else
            return -1 ;
}
void print()
{
    for(int i=0 ; i<n ; i++)
    {

        cout<<arr[i]<< " ";
    }
    cout<<endl;
}
};

template<class type>
struct Queue
{
    Array <type> q;
    int first ,last ;
    void intialize ()
    {
        q.initialize();
        first=0;
        last=0;
    }
    void destroy()
    {
        q.destroy();
        first=0;
        last=0;
    }
    void add (type t)
    {
        q.addLast(t);
        last++;
    }
    type peek ()
    {
       if(num() >0)
       {
           return q.arr[first];
       }


    }
    type pop()
    {
        if(num()>0)
        {
            return q.arr[first++];
        }
        else
            return NULL ;

    }
    int num ()
    {
        if(last<=first)
            return 0;

        return last-first;
    }
};


struct Node
{
    Array<int> adj;
    void Initialize()
    {
        adj.initialize();
    }
    void Destroy()
    {
        adj.destroy();
    }
};
struct Graph
{
    int n;
    Node* nodes;
    void Initialize(int _n)
    {
        int i;
        n=_n;
        nodes=new Node[n];
        for(i=0; i<n; i++)
            nodes[i].Initialize();
    }
    void Destroy()
    {
        int i;
        for(i=0; i<n; i++) nodes[i].Destroy();
        delete[] nodes;
    }
    void addNode(int source , int destination)
    {
        nodes[source].adj.addLast(destination);
        //nodes[destination].adj.addLast(source);
    }
};
void BFS(Graph& g, int s)
{
    Queue <int> q;
    q.intialize();
    int* vis=new int[g.n];
    int* dst=new int[g.n];
    int* pre=new int[g.n];
    int* days= new int[g.n];
    memset(vis, 0, ((sizeof(int))*g.n));
    memset(pre, -1, ((sizeof(int))*g.n));
    for(int j=0; j<g.n; j++)
        dst[j]=g.n;
    vis[s]=1;
    dst[s]=0;
    q.add(s);
    while(q.num())
    {
        int cur=q.pop();
        for(int i=0; i<g.nodes[cur].adj.n; i++)
        {
            int x=g.nodes[cur].adj[i];
            if(!vis[x])
            {
                vis[x]=1;
                pre[x]=cur;
                dst[x]=dst[cur]+1;
                days[dst[x]]++;
                q.add(x);
            }
        }
    }

    int maX=days[0];
    for(int j=1;j<g.n;j++)
    {
        if(days[j]>maX)
        {
            maX=days[j];

        }
    }
    int result;
    for(int j=0;j<g.n;j++)
    {
        if(days[j]==maX){result=j;break;}
    }
    cout<<days[result]<<" "<<result<<endl;


}

int main()
{
    Graph g;
    int numOfEmployess;
    cin>>numOfEmployess;
    g.Initialize(numOfEmployess);
    int counter=0;
    while(counter < numOfEmployess)
    {
        int friendsNum;
        cin>>friendsNum;
        for(int i=0;i<friendsNum;i++)
        {
            int friendd;
            cin>>friendd;
            g.addNode(counter,friendd);
        }
        counter++;
    }
    int casesNum;
    cin>>casesNum;
    for(int i=0;i<casesNum;i++)
    {
        int casei;
        cin>>casei;
        if(g.nodes[casei].adj.n==0)
        {
            cout<<0<<endl;
        }
        else
        {
            BFS(g,casei);
        }
    }
    return 0;
}
