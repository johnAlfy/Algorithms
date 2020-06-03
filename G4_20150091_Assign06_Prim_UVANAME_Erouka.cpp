// GROUP:   G4
// ID:      20150091
// Assign:  06
// Assign:  Prim
// UVA:     534
// Name1:   john alfy khalil
// Name2:   remon salem saber
// UVA Username: Erouka

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <math.h>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
    n--;
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


////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Edge
{
	int		v;  // id of the adjacent node
	double	w;  // edge weight = distance between the two nodes
};

struct Node
{
	int x , y ; // x and y coordinates of the node
	Array<Edge> adj;

	void Initialize(){adj.initialize() ;}
	void Destroy(){adj.destroy() ;}
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
};
double Sqrt(double v, int n=100)
{
    double a=0 , b=v , s;
    for(int i=0;i<n;i++)
    {
        s=(a+b)/2;
        if(s*s<v){a=s;}
        else{b=s;}
    }
    return s;
}

int main()
{
    Graph g;
    g.Initialize(2);
    for(int i = 0 ; i < g.n ; i++)
    {
        int x, y ;
        cin>>x ;
        cin>>y ;
        g.nodes[i].x=x;
        g.nodes[i].y=y;

    }
    for(int i=0 ; i<g.n ; i++)
    {
        for(int j=0; j<g.n ;j++)
        {
            if(i==j)continue;
            else
                {
                    Edge e;
                    e.v=j;
                    double x1 =g.nodes[i].x;
                    double x2= g.nodes[j].x;
                    double y1=g.nodes[i].y;
                    double y2=g.nodes[j].y;
                    double dis=pow((x1-x2),2) + pow((y1-y2),2);
                    e.w= Sqrt(dis);
                    //cout<<"from "<<i<<"to "<< e.v<<" costs "<<e.w<<endl ;
                    g.nodes[i].adj.addLast(e);
                }
        }
    }

    g.Destroy();
    cout << "Hello world!" << endl;
    return 0;
}
