// 자원 캐기 (DP)
// https://www.acmicpc.net/problem/14430


// F(i, j) : i, j 위치까지의 최대 광석 개수
// F(i - 1, j) = 위쪽에서 내려오는 경우,   F(i, j - 1) = 왼쪽에서 오른쪽으로 오는 경우

// 점화식
// F(i, j) = max(F(i - 1, j), F(i, j - 1)) + 현재 위치 값

// 초기값
// (i == 0)  F(i, j) = F(i, j - 1) + 현재 위치 값
// (j == 0)  F(i, j) = F(i, j - 1) + 현재 위치 값
// (i == 0 && j == 0)  F(i, j) = 현재 위치 값





// F(i, j) 위치까지의 최대 광석 개수
// max(F(i, j - 1) 위치까지의 최대 광석 개수, F(i - 1, j) 위치까지의 최대 광석 개수)

#include <iostream>
#include <algorithm>
using namespace std;

int board[301][301] = { 0 };
int mem[301][301] = { 0 };

int F(int i, int j)
{
    if (i == 0 && j == 0)
        return board[i][j];

    if (i == 0)
        return F(i, j - 1) + board[i][j];

    if (j == 0)
        return F(i - 1, j) + board[i][j];

    if (mem[i][j] != 0)
        return mem[i][j];

    return mem[i][j] = max(F(i - 1, j), F(i, j - 1)) + board[i][j];
}

int main()
{
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            int t;
            cin >> t;
            board[i][j] = t;
        }
    }

    cout << F(n - 1, m - 1);
    return 0;
}