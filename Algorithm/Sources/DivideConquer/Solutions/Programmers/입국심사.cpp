
// 입국 심사
// https://programmers.co.kr/learn/courses/30/lessons/43238

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;
using ll = long long;

// 심사하는데 걸리는 시간을 탐색대상으로 잡는다.
// 걸리는 시간의 가능한 최소, 최대값 범위를 시작으로, left와 right 범위를 축소시켜나간다.
ll Search(const vector<int>& times, ll n, ll left, ll right)
{
    if (left == right)
        return left;

    ll mid = left + (right - left) / 2;
    ll sum = 0;

    for (ll time : times)
        sum += mid / time;
    
    if (sum >= n)
        return Search(times, n, left, mid);
    else
        return Search(times, n, mid + 1, right);
}

long long solution(int n, vector<int> times) 
{
    sort(begin(times), end(times));
    ll maxtime = times[times.size() - 1] * n;
    return Search(times, n, 0, maxtime);
}

int main()
{
    int n = 6;
    vector<int> times = { 7, 10 };

    cout << solution(n, times);

    return 0;
}

