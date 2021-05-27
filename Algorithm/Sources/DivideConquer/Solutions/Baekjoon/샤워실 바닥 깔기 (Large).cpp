
// 샤워실 바닥 깔기 (Large)
// https://www.acmicpc.net/problem/14601

// 시행착오
// 1. level을 인자로 넘겨서 증가시키는 경우 중복되는 숫자가 있었음

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
//#include "Print.h"
using namespace std;

struct Vec
{
    int i, j;
};

struct FromToTarget
{
    Vec from;
    Vec to;
    Vec target;
};

bool InRange(Vec from, Vec to, Vec target)
{
    return
        from.i <= target.i && target.i <= to.i &&
        from.j <= target.j && target.j <= to.j;
}

int level = 0;
void Tile(vector<vector<int>>& board, Vec from, Vec to, Vec target)
{
    const int N = (to.i - from.i) + 1;
    if (N == 1)
        return;

    int mi = from.i + N / 2 - 1;
    int mj = from.j + N / 2 - 1;
    level++;

    vector<FromToTarget> from_to_target =
    {
        {from, {mi, mj}, {mi, mj}},
        {{from.i, mj + 1}, {mi, to.j}, {mi, mj + 1}},
        {{mi + 1, from.j}, {to.i, mj}, {mi + 1, mj}},
        {{mi + 1, mj + 1}, {to.i, to.j}, {mi + 1, mj + 1}},
    };

    for (auto& e : from_to_target)
    {
        // target이 어느 사분면에 있는지?
        if (InRange(e.from, e.to, target))
            e.target = target;
        else
            board[e.target.i][e.target.j] = level;        
    }

    for (const auto& e : from_to_target)
    {
        Tile(board, e.from, e.to, e.target);
    }
}

int main()
{
    int k = 0;
    int n = 0;
    Vec target;
    cin >> k;
    cin >> target.i >> target.j;

    n = 1 << k;
    target = { n - target.j, target.i - 1 };

    vector<vector<int>> board(n, vector<int>(n, 0));
    board[target.i][target.j] = -1;
    Tile(board, { 0, 0 }, { n - 1, n - 1 }, target);
    
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }

    return 0;
}
