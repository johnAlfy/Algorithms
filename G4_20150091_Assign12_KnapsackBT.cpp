// GROUP:   G4
// ID:      20150091
// Assign:  12
// Assign:  KnapsackBT
// UVA:     10130
// Name:    john alfy khalil
// UVA Username: Erouka
#include <bits/stdc++.h>
using namespace std;

template <class type>
void Merge(type*a, int n,bool (*isbefore)(type &a, type &b))
{
    int mid = n/2;
    int i = 0, j = mid, k;
    type * t = new type[n];
    for(k = 0 ; k < n; ++k)
    {
        if (j == n || (i < mid) && isbefore(a[i],a[j]))
            t[k] = a[i++];
        else
        {
            t[k] = a[j++];
        }
    }
    for( i = 0 ; i < n; ++i)
        a[i] = t[i];
    delete[] t;
}

template < class type>
void MergeSort(type *arr, int sz, bool (*isbefore)(type &a, type &b))
{
    if (sz <= 1)
        return ;
    int mid = sz/2;
    MergeSort<type>(arr,mid,isbefore);
    MergeSort<type> (arr+mid,sz-mid,isbefore);
    Merge<type>(arr,sz,isbefore);
}
struct Obj
{
	int v;
	int w;
};

int Size;
Obj a[1000];
bool IsBefore(Obj& a, Obj& b) // return true if unit value of a is greater than unit value of b
{
    return  double(a.v)/double(a.w) > double(b.v)/double(b.w);
}

int bestValue;
int Bound(int i, int w) // upper bound on the total value of items [i..n-1] that can fit in w
{
    int upperBound = 0,c ;
    for(c = i ; c < Size; c++){
        if (w >= a[c].w)
        {
            upperBound += a[c].v;
             w -= a[c].w;
        }
        else
            break;
    }
    if (w > 0 && c != Size)
    {
        upperBound += double(w)/double(a[c-1].w)*a[c-1].v;
    }
    return upperBound;
}

void BackTrack(int i, int w, int currentValue)
{
    if (i == Size)
    {
        if (currentValue >= bestValue)
            bestValue = currentValue;
        return ;
    }
    if (a[i].w <= w){
        BackTrack(i+1,w-(a[i].w),currentValue+a[i].v);
    }

    /// using branch and bound pardigm...
    int upperBound = Bound(i,w);
    int maxProfit = upperBound + currentValue;
    if (maxProfit <= bestValue)
        return;

    BackTrack(i+1,w,currentValue);
}

int ComputeKnapsack(int N, int W)
{
    bestValue = 0;
    BackTrack(0,W,0);
    return bestValue;
}

void Compute(){
    int testCases,G,MW;
    cin>>testCases;
    while(testCases--)
    {
        memset(a,0,sizeof a);
        cin>>Size;
        for(int i = 0 ; i < Size; ++i)
        {
            cin>>a[i].v;
            cin>>a[i].w;
        }
        MergeSort(a,Size,IsBefore);
        cin>>G;
        int ans = 0;
        for(int i = 0 ; i < G ; ++i)
        {
            cin>>MW;
            ans += ComputeKnapsack(Size,MW);
        }
        cout << ans << endl;
    }
}


int main()
{
	Compute();
	return 0;
}

