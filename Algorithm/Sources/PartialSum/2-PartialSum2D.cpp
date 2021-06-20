
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

void PartialSum(int n)
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 1; j < n; ++j)
        {
            psum[i][j] = psum[i][j - 1] + v[i][j];
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
    PartialSum(4);
    cout << GridSum(1, 1, 2, 2);

    return 0;
}
