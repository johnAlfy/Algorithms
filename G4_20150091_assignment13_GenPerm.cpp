// GROUP:   G4
// ID:      20150091
// Assign:  13
// Assign:  GenPerm
// UVA:     216
// Name:    john alfy khalil
// UVA Username: Erouka

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>      // use built-in sqrt()
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define MAX_COMPUTERS 8

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Point{int x,y;};
double Dist(Point& a, Point& b)
{
    double dis =sqrt( (a.x - b.x)*(a.x - b.x) +
    (a.y - b.y)*(a.y - b.y)
               )+16;

    return dis;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int		n; // number of computers (input)
Point	com[MAX_COMPUTERS]; // locations of computers (input)
double	dist[MAX_COMPUTERS][MAX_COMPUTERS]; // dist[i][j]=distance from com[i] to com[j] (pre-computed)

////////////////////////////////////////////////////////////////////////////////////////////////////////////

double	best_val=1e9; // best value until now
int		best_sol[MAX_COMPUTERS]; // best solution until now (a permutation)

int		s[MAX_COMPUTERS]; // s is current permutation. s[i]=index of the ith computer in this permutation.

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void UpdateSol()// evaluate the permutation s, then update best_val and best_sol if necessary
{
    double distance=0;
    for(int i=0 ; i<n-1 ; i++)
    {
        distance+=Dist(com[s[i] ],com[s[i+1]]);
    }

    if(distance < best_val)
    {
        best_val=distance;
        for(int i=0 ; i <n ; i++)
        {
            best_sol[i]=s[i];
        }
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Backtrack0(int i) // backtrack using swaps
{
    if(i==n)
    {
        UpdateSol();
        return;
    }

    for(int j=i ; j<n ;j++)
    {
        swap(s[i],s[j]);
        Backtrack0(i+1);
        swap(s[i],s[j]);
    }
}
void Compute0() // do necessay initializations and call Backtrack0()
{
    for(int i=0 ; i<n ; i++)
    {
        s[i]=i;
    }
    memset(com,0,sizeof com);
    memset(dist,0,sizeof dist);
    memset(best_sol,0,sizeof best_sol);
    Backtrack0(0);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool v[MAX_COMPUTERS]; // v[i]=true if com[i] already taken in the permutation

void Backtrack1(int i) // backtrack using the v[] array
{
    if(i==n)
    {
        UpdateSol();
        return;
    }
    for(int j=0 ; j<n ; j++)
    {
        if(!v[j])
        {
            s[i]=j;
            v[j]=true;
            Backtrack1(i+1);
            v[j]=false;
        }
    }
}
void Compute1() // do necessay initializations and call Backtrack1()
{
    memset(v,false,sizeof v);
    memset(s,0,sizeof s);
    memset(com,0,sizeof com);
    memset(dist,0,sizeof dist);
    memset(best_sol,0,sizeof best_sol);
    Backtrack1(0);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Dancing Links:

int F[MAX_COMPUTERS+1]; // head=F[0], elements are indexed from 1 to n, F[n]=0
int B[MAX_COMPUTERS+1]; // B[0]=n, B[1]=0
void Remove(int i) {F[B[i]]=F[i]; B[F[i]]=B[i];}
void Restore(int i) {B[F[i]]=i; F[B[i]]=i;}
void InitDancingLinks(int n)
{
	int i;
	for(i=0;i<n;i++) F[i]=i+1; F[n]=0;
	for(i=n;i>0;i--) B[i]=i-1; B[0]=n;
}
// for(i=F[0];i!=0;i=F[i]) iterate on available list indexes

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Backtrack2(int i) // backtrack using dancing links
{
     if(i==n)
    {
        UpdateSol();
        return;
    }
    for(int j=F[0] ; j!=0 ;j=F[j])
    {
        s[i]=j-1;
        Remove(j);
        Backtrack2(i+1);
        Restore(j);
    }
}
void Compute2() // do necessay initializations and call Backtrack2()
{
    InitDancingLinks(n);
    memset(s,0,sizeof s);
    memset(com,0,sizeof com);
    memset(dist,0,sizeof dist);
    memset(best_sol,0,sizeof best_sol);
    Backtrack2(0);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ComputeCore()
{
	// do necessay initializations of dist[][] and best_val
//	Compute0();
	Compute1();
	//Compute2();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Compute() // get input and then call ComputeCore(); then print output
{
    cin>>n ;
    for(int i=0;i<n ;i++)
    {
        cin>>com[i].x ;
        cin>>com[i].y;
    }
    ComputeCore();
    cout<<best_val;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	//freopen("input_assign13_00216.txt", "r", stdin);
	Compute();

	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
