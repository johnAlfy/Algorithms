#include <iostream>
#include <cmath>
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
template<class T>
struct Heap{
Array<T> arr;

bool(*isBefore) ( int &a, int &b);
void initialize( bool(*__isBefore)(int & ,int & ) )
{
    isBefore=(*__isBefore);
    arr.initialize();
}
void destroy()
{
arr.destroy();
}
void print()
{
    arr.print();
}
int child(int i)
{
    int p =(2*i)+1;
    if(p > arr.n-1)
    {
        return -1 ;
    }

    return p;
}
int parent(int i)
{
    if(i==0)
    {
        return -1 ;
    }
    return ceil((double)i/2)-1;
}
T getFirst()
{
 return arr[0];
}
T retrieveFirst()
{
    T first_elem=arr[0];
    arr[0]=arr[arr.n-1];
    arr.removeLast();
    moveDown(0);
    return first_elem;
}
void add(T e)
{
    arr.addLast(e);
    moveUp(arr.n-1);
}
void moveUp(int i)
{
    int par=parent(i);
    if(par != -1 && isBefore( arr[i] , arr[par] ) )
    {
       swap(arr[i],arr[par]);
       moveUp(par);

    }
}
void moveDown(int i)
{
    int selected_child=child(i);
    if(selected_child==-1)
        return;
    int right_child = selected_child + 1;
    if(isBefore(arr[right_child],arr[selected_child]) && right_child != -1 )
    {
    selected_child=right_child;
    }
    if(isBefore(arr[selected_child],arr[i] ))
    {
        swap(arr[i],arr[selected_child]);
        moveDown(selected_child);
    }
}



};
bool isBeforeInt(int& a, int& b)
{
	return (a <= b);
}

int main()
{


    int comulutiveSum = 0;
 while (true)
 {
     Heap <int> c;
     c.initialize(isBeforeInt);
     int x;
     cin>> x ;
     if(x==0)
     {
        return 0;
     }

     for(int i=0 ; i <x ; i++)
     {
         int num ;
         cin>> num ;
         c.add(num);
     }
     int sum=0;

    while(c.arr.n > 1 )
     {
        int first=c.getFirst();
        c.retrieveFirst();
        first+=c.getFirst();
        c.retrieveFirst();
        sum+=first;


        c.add(first);
     }

    cout<<sum<< endl;
 }
    return 0;
}
