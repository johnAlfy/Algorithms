// GROUP:   G4
// ID:      20150091
// Assign:  04
// Assign:  countInv
// UVA:     10810
// Name:    Erouka


#include <iostream>

using namespace std;
long long CountInvMerge(long long* a, int n)
{
    int mid =(n/2);
    if(n<=1)
    {
        return 0;
    }
    int i=0,j=mid,k;
    long long int value=0;
    int *t=new int [n];
    for( k=0; k<n; k++)
    {
        if(j==n||( i<mid && a[i]<=a[j]))
        {
            t[k]=a[i++];

        }
        else
        {
            value+=mid-i;
            t[k]=a[j++];
        }
    }
    for(i=0; i<n; i++)
    {
        a[i]=t[i];
    }
    delete []t;
    return value;

};
long long CountInv(long long* a, int n)
{
    int mid=n/2;
    if(n<=1)
    {
        return 0;
    }
    return CountInv(a,mid)+CountInv(mid+a,n-mid)+CountInvMerge(a,n);
};
int main()
{
 long long *arr ;
 long long x ;
while (true)
{

    cin>>x;
    if(x==0)
    {
        return 0;
    }
    arr=new long long[x];
    for(int i=0 ; i<x ; i++)
    {
        long long f;
        cin>>f;
        arr[i]=f;
    }
    long long v=CountInv(arr,x);
    cout<<v<<endl;;

}
    return 0;
}
