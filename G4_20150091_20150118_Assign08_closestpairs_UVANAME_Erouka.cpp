// GROUP:   G4
// ID:      20150091 , 20150118
// Assign:  08
// Assign:  ClosetsPair
// UVA:     10245
// Name1:   john alfy khalil
// Name2:   Remon Salem Saber
// UVA Username: Erouka

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Type>
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

template<class Type>
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Point
{
    double x,y;
};

bool IsBeforeX(Point& a, Point& b)
{
    return a.x<b.x;
};
bool IsBeforeY(Point& a, Point& b)
{
    return a.y<b.y;
};

float dist(Point p1, Point p2)
{
    return sqrt( (p1.x - p2.x)*(p1.x - p2.x) +
                 (p1.y - p2.y)*(p1.y - p2.y)
               );
}
float bruteForce(Point *arr, int Size)
{
    float MIN = 1000000000 ;
    for (int i = 0; i < Size; ++i)
    {
        for (int j = i+1; j < Size; ++j)
        {
            if (dist(arr[i], arr[j]) < MIN)
            {
                MIN = dist(arr[i], arr[j]);
            }
        }
    }
    return MIN;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
float stripClosest(Point *arr, int Size, float d)
{
    float MIN = d;
    MergeSort(arr,Size,IsBeforeY);
    for (int i = 0; i < Size; i++)
        for (int j = i+1; j < Size && (arr[j].y - arr[i].y) < MIN ; j++)
            if (dist(arr[i],arr[j]) < MIN)
                MIN = dist(arr[i], arr[j]);

    return MIN;
}



// Sort the points p according to x before calling this function
float ClosestPair(Point* P, int n)
{
    if (n <= 3)
        return bruteForce(P, n);

    int mid = n/2;
    Point midPoint = P[mid];

    float dl = ClosestPair(P, mid);
    float dr = ClosestPair(P + mid, n-mid);


    float d = min(dl, dr);
    Point strip[n];
    int j = 0;
    for (int i = 0; i < n; i++)
    {
        if (abs(P[i].x - midPoint.x) < d)
            strip[j++] = P[i] ;

    }

    return (float) min(d, stripClosest(strip, j, d) );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    while(true)
    {
        int N ;
        cin >>N;
        if(!(N>=0 && N<=10000) || N==0)return 0;
        Point *arr=new Point[N];
        for(int i=0 ; i<N ; i++)
        {
            int x,y ;
            cin>>x;
            cin>>y;
            arr[i].x=x;
            arr[i].y=y;
        }
        double destance=ClosestPair(arr,N);
        if(destance>=10000)
            cout<<"INFINITY"<<endl;
        else
            cout<<setprecision(4)<<fixed<<destance<<endl;

    }

    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
