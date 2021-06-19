

#pragma warning (disable : 4996)
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

vector<long long> psum(100000, 0);

long long RangeSum(int from, int to)
{
    if (from == 0) return psum[to];
    return psum[to] - psum[from - 1];
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; ++i)
        scanf("%d", &psum[i]);

    partial_sum(begin(psum), end(psum), begin(psum));

    for (int i = 0; i < m; ++i)
    {
        int from, to;
        scanf("%d %d", &from, &to);
        printf("%d\n", RangeSum(from - 1, to - 1));
    }

    return 0;
}