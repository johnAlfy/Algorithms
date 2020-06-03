// GROUP:   G4
// ID:      20150091_20150118
// Assign:  07
// Assign:  Dijkstra
// UVA:     10986
// Name1:   john alfy khalil
// Name2:   remon salim saber
// UVA Username: Erouka

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Value>
struct Array
{
	int  n, sz;
	Value* arr;
void Initialize(){

    sz=1;
    n=0;
    arr=new Value[sz];
    };
	void Destroy(){
	    delete[]arr;
	    };
	void AddLast(Value v)
	{
	if(n==sz){
        sz*=2;
    Value *new_arr=new Value[sz];
    for(int i=0;i<n;i++)
        {
        new_arr[i]=arr[i];
        }
        delete arr;
        arr=new_arr;
    }
    arr[n++]=v;

	};
	void RemoveLast()
	{
	    n--;
	};
	Value& operator[](int i)
	{
	    return arr[i];
	};
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Elem>
struct Heap
{
	int* pos; // pos[v]=i where a[i].v=v, otherwise pos[v]=-1
	Array<Elem> a;
	bool (*IsBefore)(Elem&, Elem&);

		void Initialize (bool (*_IsBefore)(int&, int&)){
	IsBefore=_IsBefore;
    a.Initialize();

	};
	void Destroy(){
	a.Destroy();
	};
	void print()
{
    a.print();
}
	int Child(int i){
	    int x=2*i+1;
	    if(x > a.n-1)
    {
        return -1 ;
    }
	    return x;
	    }
	int Parent(int i){
	    if(i==0)
    {
        return -1 ;
    }
	    return (i-1)/2;
	    };

	void MoveUp(int ind){
	int par= Parent(ind);
	if(par==-1){
	return;
	}
	bool x=IsBefore(a.arr[par],a.arr[ind]);
	if(x==false){
        Elem y=a.arr[par];
        a.arr[par]=a.arr[ind];
        a.arr[ind]=y;
        MoveUp(par);
	}


	};

	void MoveDown(int ind){
	    int chil= Child(ind);
	    if(chil==-1){
            return ;
	    }
	    int sec_child=chil+1;
	    if(IsBefore(a.arr[sec_child],a.arr[chil]) && sec_child <=a.n )
    {
    chil=sec_child;
    }
    if(IsBefore(a.arr[chil],a.arr[ind] ))
    {
        Elem y=a.arr[chil];
        a.arr[chil]=a.arr[ind];
        a.arr[ind]=y;
        MoveDown(chil);
    }
	    };
	void Add(Elem e){
	a.AddLast(e);
	MoveUp(a.n-1);

	};
	Elem GetFirst(){
	    return a.arr[0];
	    };
	Elem RetrieveFirst()
	{
	     Elem x=a.arr[0];
    a.arr[0]=a.arr[a.n-1];
    a.RemoveLast();
    MoveDown(0);
    return x;
	};
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Edge
{
	int		v;
	int		f;
	int    t;

};

struct Node
{
	Array<Edge> adj;

	void Initialize()
	{
	adj.Initialize();
	};
	void Destroy()
	{
	adj.Destroy();
	};
};

struct Graph
{
	int n;
	Node* nodes;


	void Initialize(int _n){
	   int i;
    n=_n;
    nodes=new Node[n];
    for(i=0;i<n;i++)
        {
             nodes[i].Initialize();
             };
	};
	void Destroy()
	{
	     int i;
    for(i=0;i<n;i++){
            nodes[i].Destroy();
    }
        delete[] nodes;
	};
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool IsBefore(Edge& a, Edge& b)
{
	return a.v<b.v;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{

    int N,n,m,s,t;
    Graph g;
    cin>>N;
    Edge e;
    if(N==0){return 0;}
    while(N>0){
        cin>>n;
         g.Initialize(n);
         cin>>m;
         cin>>s>>t;
         for(int i=0;i<m;i++){
            int fr,to,v;
            cin>>fr>>to>>v;
            fr=e.f;
            to=e.t;
            v=e.v;

            g.nodes[i].adj.AddLast(e);
         }
         int count=0;
         int x=0;
         for(int i=0;i<m;i++){
            if(g.nodes[i].adj.arr[i].f==s){
                x=g.nodes[i].adj.arr[i].f;

            }
         }
         while (x!=to){
         for(int i=0;i<m;i++){
                if(x==t){break;}
            if(g.nodes[i].adj.arr[i].f=x){
                count +=g.nodes[i].adj.arr[i].v;
                x=g.nodes[i].adj.arr[i].f;
            }
         }

         }


        N++;
    }

	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
