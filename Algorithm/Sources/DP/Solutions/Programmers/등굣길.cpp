
// 등굣길 (DP)
// https://programmers.co.kr/learn/courses/30/lessons/42898

// 시행착오
// 1. 초기값 세팅 문제,
/*
아래 코드를
if (arr[i - 1][1] < 0)
{
    arr[i][1] = 0;
}

아래 코드로 변경
if (arr[i][1] < 0)
{
    arr[i][1] = 0;
}
*/


#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <map>
using namespace std;
using ll = long long;

class Modular
{
public:
    // (a + b) % m
    static long long Sum(long long a, long long b, long long m)
    {
        return ((a % m) + (b % m)) % m;
    }

    // (a - b) % m
    static long long Sub(long long a, long long b, long long m)
    {
        return ((a % m) - (b % m) + m) % m;
    }

    // (a * b) % m
    static long long Mul(long long a, long long b, long long m)
    {
        return ((a % m) * (b % m)) % m;
    }
};


ll arr[101][101] = { 0 };
int solution(int m, int n, vector<vector<int>> puddles)
{
    const ll kInvalid = -1;
    for (auto v : puddles)
    {
        arr[v[1]][v[0]] = kInvalid;
    }
    arr[1][1] = 1;
    for (int i = 2; i <= n; ++i)
    {
        if (arr[i][1] < 0)
        {
            arr[i][1] = 0;
        }
        else
        {
            arr[i][1] = arr[i - 1][1];
        }
    }

    for (int j = 2; j <= m; ++j)
    {
        if (arr[1][j] < 0)
        {
            arr[1][j] = 0;
        }
        else
        {
            arr[1][j] = arr[1][j - 1];
        }
    }

    for (int i = 2; i <= n; ++i)
    {
        for (int j = 2; j <= m; ++j)
        {
            if (arr[i][j] < 0)
            {
            }

            else
            {
                if (arr[i - 1][j] < 0 && arr[i][j - 1] < 0)
                {
                    arr[i][j] = 0;
                }
                else if (arr[i - 1][j] < 0)
                {
                    arr[i][j] = arr[i][j - 1];
                }
                else if (arr[i][j - 1] < 0)
                {
                    arr[i][j] = arr[i - 1][j];
                }
                else
                {
                    arr[i][j] = Modular::Sum(arr[i - 1][j], arr[i][j - 1], 1000000007LL);
                }
            }
        }
    }

    //Print::Board<ll, 101, 101>(arr, n + 1, m + 1);
    return arr[n][m];
}