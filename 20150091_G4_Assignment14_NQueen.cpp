// GROUP:   G4
// ID:      20150091
// Assign:  14
// Assign:  NQueen
// UVA:     11195
// Name:    John Alfy Khalil
// UVA Username: Erouka

#include <bits/stdc++.h>
using namespace std;
int boardRows[20],ans;
char chessBoard[20][20];

bool Available(int col, int row) {
    for (int prev = 1; prev < col; prev++)
    {
        if (boardRows[prev] == row || (abs(boardRows[prev] - row) == abs(prev - col)))
            return false;
    }
  return true;
}

void NQueenBackTrack(int col, int n)
{
    for (int row = 1; row <= n; row++)
    {
        if (chessBoard[row][col] != '*' && Available(col, row) )
        {
            boardRows[col] = row;
            if (col == n) ans++;
            else
            {
                NQueenBackTrack(col+1 , n);
                boardRows[col] = '.';
            }
        }
    }
}


int main() {
    int n,cnt=0;
    while (true)
    {
        cin >> n;
        if (n == 0)
            return 0;
        memset(boardRows, 0, sizeof boardRows);
        for(int i = 1 ; i <= n; ++i)
        {
            for(int k = 1 ; k <= n; ++k)
            {
                cin >> chessBoard[i][k];
            }
        }
        NQueenBackTrack(1,n);
        cout << "Case " << ++cnt <<": " << ans << endl;
        ans = 0 ;
    }
  return 0;
}

