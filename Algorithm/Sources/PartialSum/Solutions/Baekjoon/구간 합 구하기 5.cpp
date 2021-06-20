
// 구간 합 구하기 5 (부분합)
// https://www.acmicpc.net/problem/11660

#pragma warning (disable : 4996)
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

long long psum[1024][1024] = { 0 };

void PartialSum(int n)
{
    for (int i = 0; i < n; ++i) 
    {
        for (int j = 1; j < n; ++j)
        {
            psum[i][j] += psum[i][j - 1];
        }
    }

    for (int j = 0; j < n; ++j)
    {
        for (int i = 1; i < n; ++i)
        {
            psum[i][j] += psum[i - 1][j];
        }
    }
}

long long GridSum(int y1, int x1, int y2, int x2)
{
    long long ret = psum[y2][x2];
    if (y1 > 0) ret -= psum[y1 - 1][x2];
    if (x1 > 0) ret -= psum[y2][x1 - 1];
    if (y1 > 0 && x1 > 0) return ret += psum[y1 - 1][x1 - 1];
    return ret;
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            scanf("%d", &psum[i][j]);

    PartialSum(n);

    for (int i = 0; i < m; ++i)
    {
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        printf("%d\n", GridSum(x1 - 1, y1 - 1, x2 - 1, y2 - 1));
    }

    return 0;
}
