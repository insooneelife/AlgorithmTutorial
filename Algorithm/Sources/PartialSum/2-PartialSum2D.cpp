
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

long long v[4][4] = 
{
    1, 2, 3, 4,
    2, 3, 4, 5,
    3, 4, 5, 6,
    4, 5, 6, 7
};

long long psum[4][4] =
{
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0
};

// 2차원 배열의 부분합
void PartialSum(int n)
{
    // 각 행에 대한 부분합을 먼저 구한다.
    for (int i = 0; i < n; ++i)
    {
        for (int j = 1; j < n; ++j)
        {
            psum[i][j] = psum[i][j - 1] + v[i][j];
        }
    }

    // 행 단위로 부분합을 누적시킨다.
    for (int j = 0; j < n; ++j)
    {
        for (int i = 1; i < n; ++i)
        {
            psum[i][j] += psum[i - 1][j];
        }
    }
}

// 행 : y, 열 : x
// y1, x1 부터 y2, x2 까지의 직사각형 구간의 합
// 0으로 시작하는 인덱스는 예외처리
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
    PartialSum(4);
    cout << GridSum(1, 1, 2, 2);

    return 0;
}


// 연습 문제 
// 구간 합 구하기 5 (부분합)
// https://www.acmicpc.net/problem/11660