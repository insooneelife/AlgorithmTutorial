// 땅따먹기
// https://programmers.co.kr/learn/courses/30/lessons/12913

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

using ll = long long;

ll mem[100000][4] = {};

ll F(const vector<vector<int>>& land, int n, int k)
{
    if (n == 0)
        return land[n][k];

    if (mem[n][k] != 0)
        return mem[n][k];

    ll max_val = 0;
    for (int i = 0; i < 4; ++i)
    {
        if (i == k)
            continue;

        max_val = max(max_val, F(land, n - 1, i));
    }
    return mem [n][k] = max_val + (ll)land[n][k];
}

int solution(vector<vector<int>> land)
{
    ll max_val = 0;
    for (int i = 0; i < 4; ++i)
    {
        max_val = max(max_val, F(land, land.size() - 1, i));
    }

    return max_val;
}

int main()
{
    vector<vector<int> > land = { 
        {1, 2, 3, 5},
        {5, 6, 7, 8},
        {4, 3, 2, 1} 
    };

    cout << solution(land);

    return 0;
}