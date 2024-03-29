﻿// 땅따먹기
// https://programmers.co.kr/learn/courses/30/lessons/12913

// 문제풀이
// 점화식
// F(n, k) : n, k 위치까지 내려오며 얻을 수 있는 최대 점수

// n, k 위치까지 얻을 수 있는 최대점수는
// n - 1, 0 위치까지의 최대점수,
// n - 1, 1 위치까지의 최대점수,
// n - 1, 2 위치까지의 최대점수,
// n - 1, 3 위치까지의 최대점수,
// 위 경우들 중에서 열 번호가 k와 다른 경우의 최대점수들 중 가장 큰 값 + 현재 점수

// 점화식
// F(n, k) = max(for l : F(n - 1, l)) + land[n][k]  (l은 k가 아닌 [0, k] 범위의 값)

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