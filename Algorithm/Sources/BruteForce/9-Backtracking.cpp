// 백트래킹


// N-Queen
// https://www.acmicpc.net/problem/9663


#include <iostream>
#include <vector>
using namespace std;

int arr[15][15] = {};

void PrintBoard(int n, string tag)
{
    cout << tag << endl;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

bool InBoard(int n, int si, int sj)
{
    return
        0 <= si && si < n &&
        0 <= sj && sj < n;
}

void SetBoard(int n, int si, int sj, int flag)
{
    vector<pair<int, int>> directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {-1, -1}, {1, 1}, {-1, 1}, {1, -1} };

    arr[si][sj] += flag;
    for (auto dir : directions)
    {
        int mi = dir.first;
        int mj = dir.second;

        int next_i = si + mi;
        int next_j = sj + mj;

        while (InBoard(n, next_i, next_j))
        {
            arr[next_i][next_j] += flag;

            next_i = next_i + mi;
            next_j = next_j + mj;
        }
    }
}

int cnt = 0;
void SetQueen(int n, int line)
{
    if (line == n)
    {
        cnt++;
        return;
    }

    for (int i = 0; i < n; ++i)
    {
        if (arr[line][i] <= 0)
        {
            SetBoard(n, line, i, 1);
            SetQueen(n, line + 1);
            SetBoard(n, line, i, -1);
        }   
    }
}

int main()
{
    int n;
    cin >> n;

    SetQueen(n, 0);

    cout << cnt;

    return 0;
}













