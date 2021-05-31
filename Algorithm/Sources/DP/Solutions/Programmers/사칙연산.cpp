
// 사칙연산 (DP, MinMax)
// https://programmers.co.kr/learn/courses/30/lessons/1843

// 시행착오
// 1. 최소, 최대
// 현재의 최소가 후에 최대가 될 수 있고, 현재의 최대가 후에 최소가 될 수 있다.
// 그러므로 현재의 최소, 최대를 모두 저장하며 dp를 진행하도록 한다.

#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <functional>
using namespace std;
using ll = long long;

struct MinMax
{
    ll minv, maxv;
};

MinMax mem[202][202] = { 0 };
bool visited[202][202] = { false };

map<string, function<ll(ll, ll)>> ops =
{
    {"+", [](ll a, ll b) { return a + b; }},
    {"-", [](ll a, ll b) { return a - b; }}
};

MinMax F(const vector<string>& arr, int i, int j)
{
    if (j - i == 0)
    {
        ll val = stoll(arr[i]);
        return { val, val };
    }

    if (j - i == 2)
    {
        ll val = ops[arr[i + 1]](stoll(arr[i]), stoll(arr[j]));
        return { val, val };
    }

    if (visited[i][j])
        return mem[i][j];

    ll maxv = numeric_limits<ll>::min();
    ll minv = numeric_limits <ll>::max();
    for (int k = i; k < j; k += 2)
    {
        MinMax left = F(arr, i, k);
        MinMax right = F(arr, k + 2, j);

        vector<pair<ll, ll>> all =
        {
            { left.minv, right.minv },
            { left.minv, right.maxv },
            { left.maxv, right.minv },
            { left.maxv, right.maxv }
        };
        
        for (int i = 0; i < 4; ++i)
        {
            pair<ll, ll> comp = all[i];
            ll ret = ops[arr[k + 1]](comp.first, comp.second);
            maxv = max(maxv, ret);
            minv = min(minv, ret);
        }
    }

    visited[i][j] = true;
    return mem[i][j] = { minv, maxv };
}


int solution(vector<string> arr)
{
    return F(arr, 0, arr.size() - 1).maxv;
}


int main()
{
    vector<string> arr = { "1", "-", "3", "+", "5", "-", "8" };
    //vector<string> arr = { "5", "-", "3", "+", "1", "+", "2", "-", "4" };
    //vector<string> arr = { "1", "+", "3", "-", "5", "-", "8", "+", "999"};
    //vector<string> arr = { "999" };

    cout << solution(arr) << endl;

    return 0;
}