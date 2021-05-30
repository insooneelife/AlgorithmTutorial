
// N으로 표현 (DP)
// https://programmers.co.kr/learn/courses/30/lessons/42895

// 시행착오
// 1. 괄호치기 DP로 해결하려 접근함 -> 55, 555 처리가 어려움
// 2. F(N) = for K = [1, N - 1] F(K) + F(N - K) 로 접근함 
//    55, 555 처리를 너무 어렵게 생각함 -> 문자열로 해결하려함 -> 시간초과

#include <string>
#include <vector>
#include <iostream>
#include <functional>
#include <algorithm>
//#include "Print.h"

using namespace std;
using ll = long long;
using OperationType = function<bool(ll, ll, ll&)>;
using VectorType = vector<ll>;

const vector<OperationType> ops =
{
    [](ll a, ll b, ll& out) { out = a + b; return true; },
    [](ll a, ll b, ll& out) { out = a - b; return true; },
    [](ll a, ll b, ll& out) { out = a * b; return true; },
    [](ll a, ll b, ll& out)
    {
        if (b == 0)
            return false;
        out = a / b;
        return true;
    }
};

ll MakeNumber(int N, int cnt)
{
    ll sum = 0;
    while (cnt--)
    {
        sum += N;
        N *= 10;
    }
    return sum;
}

int solution(int N, int num) 
{
    if (N == num)
        return 1;

    vector<VectorType> dp(9);
    for (int i = 0; i < dp.size(); ++i)
    {
        dp[i].reserve(1000000);
        dp[i].push_back(MakeNumber(N, i));
    }

    for (int n = 2; n <= 8; ++n)
    {   
        for (int i = 1; i < n; ++i)
        {
            for (auto op : ops)
            {
                for(ll a : dp[i])
                {
                    for(ll b : dp[n - i])
                    {
                        ll val;
                        if(op(a, b, val))
                            dp[n].push_back(val);   

                        if (op(b, a, val))
                            dp[n].push_back(val);

                    }
                }
            }
        }

        sort(begin(dp[n]), end(dp[n]));
        auto it = unique(begin(dp[n]), end(dp[n]));
        dp[n].erase(it, end(dp[n]));

        if (binary_search(begin(dp[n]), end(dp[n]), num))
        {
            return n;
        }
    }
    
    return -1;
}

int main()
{
    int N = 5; 
    int num = 12;
    cout << solution(N, num) << endl;

    return 0;
}
