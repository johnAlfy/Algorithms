// GROUP:   G4
// ID:      20150091
// Assign:  11
// Assign:  EditDist
// UVA:     526
// Name:    John Alfy Khalil
// UVA Username: Erouka

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

char a[82];
char b[82];
int D[81][81]; // D[][] is the same for all versions (no memory reduction)

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T1[81][81];
int EditDist1(int n, int m)
{
    if (n == 0 && m == 0)
        return 0;
    if (T1[n][m] >= 0)
        return T1[n][m];
    int rep = 1e9 , ins = 1e9 , del = 1e9;
    if (n > 0)
    {

        del = 1+EditDist1(n-1,m);

    }

    if (n > 0 && m > 0)
    {

        rep = (a[n-1]!=b[m-1])+EditDist1(n-1,m-1);

    }
    if (m > 0)
    {

        ins = 1+EditDist1(n,m-1);

    }
    T1[n][m] = min(del,min(ins,rep));
    if(T1[n][m]==del)
        D[n][m]=3;
    else if(T1[n][m]==rep)
        D[n][m]=1;
    else if(T1[n][m]==ins)
        D[n][m]=2;

    return T1[n][m] ;
}
int ComputeEditDist1(int N, int M)
{
    memset(T1,-1,sizeof T1);
    return EditDist1(N,M);

} // Recursive - memoization - initialize T then call EditDist1(N,M);

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T2[81][81];
int ComputeEditDist2(int n, int m) // Bottom-up, do not save space
{
    memset(T2,-1,sizeof T2);
    for(int i = 0 ; i <= n; ++i)
    {
        for(int k = 0 ; k <= m; ++k)
        {
            int rep = 1e9, ins = 1e9, del = 1e9;
            if (i == 0 && k == 0)
                T2[i][k] = 0;
            else
            {
                if (i > 0)
                    del = 1+T2[i-1][k];
                if (i > 0 && k > 0)
                    rep = (a[i-1]!=b[k-1])+T2[i-1][k-1];
                if (k > 0)
                    ins = 1+T2[i][k-1];
                T2[i][k] = min(rep,min(del,ins));
            }
            if(T2[i][k]==del)
                D[i][k]=3;
            else if(T2[i][k]==rep)
                D[i][k]=1;
            else if(T2[i][k]==ins)
                D[i][k]=2;

        }
    }
    return T2[n][m];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T3[2][81];
int ComputeEditDist3(int n, int m) // Bottom-up, use two rows only
{
    memset(T3,-1,sizeof T3);
    int cur = 0 ;
    for(int i = 0 ; i <= n; ++i)
    {
        for(int k = 0 ; k <= m; ++k)
        {
            int rep = 1e9, ins = 1e9, del = 1e9;
            if (i == 0 && k == 0)
                T3[cur][k] = 0;
            else
            {
                if (i > 0)
                    del = 1+T3[1-cur][k];
                if (i > 0 && k > 0)
                    rep = (a[i-1]!=b[k-1])+T3[1-cur][k-1];
                if (k > 0)
                    ins = 1+T3[cur][k-1];
                T3[cur][k] = min(rep,min(del,ins));
            }
            if(T3[cur][k]==del)
                D[i][k]=3;
            else if(T3[cur][k]==rep)
                D[i][k]=1;
            else if(T3[cur][k]==ins)
                D[i][k]=2;
        }
        cur = 1-cur;
    }
    return T3[1-cur][m];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T4[81];
int ComputeEditDist4(int n, int m) // Bottom-up, save maximum space
{
     memset(T4,-1,sizeof T4);
    int previous;
    for(int i = 0 ; i <= n; ++i)
    {
        for(int k = 0 ; k <= m; ++k)
        {
            int rep = 1e9, ins = 1e9, del = 1e9;
            if (i == 0 || k == 0)
            {
                previous = T4[k];
                T4[k] = i + k;
                continue ;
            }
            else
            {
                if (i > 0)
                    del = 1 + T4[k];
                if (i > 0 && k > 0)
                    rep = (a[i-1]!=b[k-1]) + previous;
                if (k > 0)
                    ins = 1 + T4[k - 1];
                previous=T4[k];
                T4[k]= min(rep,min(del,ins));

                if(T4[k]==del)
                    D[i][k]=3;
                else if(T4[k]==rep)
                    D[i][k]=1;
                else if(T4[k]==ins)
                    D[i][k]=2;
            }
        }
    }
    return T4[m];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Oper
{
	int n,m;
	int oper;
};

Oper opers[81];

int EditDistSol(int N, int M)
{
	int n = N, m = M;
	int i = 0;
	int shiftcursor = 0;
	while (n>0 && m>0)
	{
		if (D[n][m] == 3)
		{
			Oper oper;
			oper.oper = 3;
			oper.n = n;
			n =n - 1;
			opers[i++] = oper;
			continue;
		}
		else if (D[n][m] == 1 && a[n - 1] != b[m - 1])
		{
			Oper oper;
			oper.oper = 1;
			oper.n = n;
			oper.m = b[m - 1];
			n = n - 1;
			m = m - 1;
			opers[i++] = oper;
			continue;
		}
		else if (D[n][m] == 2)
		{
			Oper oper;
			oper.oper = 2;
			oper.n = n;
			oper.m = b[m - 1];
			m =m- 1;
			opers[i++] = oper;
			continue;
		}
		n--;
		m--;
	}
	while (true)
	{
		if (n == 0 && m == 0)
            break;

		if (n == 0 && m != 0)
		{
			Oper oper;
			oper.oper = 2;
			oper.n = n;
			oper.m = b[m - 1];
			m = m - 1;
			opers[i++] = oper;
		}
		if (n != 0 && m == 0)
		{
			Oper oper;
			oper.oper = 3;
			oper.n = n;
			n = n - 1;
			opers[i++] = oper;
		}
	}
	int counter = 0;
    for (int k = i - 1; k >= 0; k--)
    {
        counter++;
        cout << counter << " ";
        Oper curr = opers[k];
        if(curr.oper==1)
            cout << "Replace " << curr.n + shiftcursor << "," << char(curr.m);
        else if(curr.oper==2)
        {
            cout << "Insert " << curr.n + 1 + shiftcursor << "," << char(curr.m);
            shiftcursor++;
        }
        else if (curr.oper==3)
        {
            cout << "Delete " << curr.n + shiftcursor;
            shiftcursor--;
        }
        cout << endl;
    }

	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ComputeEditDist(int N, int M) // Here we can choose the method
{
	//return ComputeEditDist1(N,M);
	//return ComputeEditDist2(N,M);
	//return ComputeEditDist3(N,M);
	return ComputeEditDist4(N,M);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// This function does not need any modification:
void Compute() // Get input and call ComputeEditDist() whenever needed
{
	int cas=0;
	while(true)
	{
		a[0]=0; b[0]=0;
		if(!fgets(a,82,stdin)) break; fgets(b,82,stdin);
		a[strlen(a)-1]=0;
		b[strlen(b)-1]=0;
		int N=strlen(a), M=strlen(b);
		cout<<ComputeEditDist(N,M)<<endl;
		//if(cas) cout<<endl;
		EditDistSol(N,M);
		cas++;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	//freopen("input_assign11_00526.txt", "r", stdin);
	Compute();
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
