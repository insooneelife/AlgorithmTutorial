
// 야근 지수 (탐욕법, 힙)
// https://programmers.co.kr/learn/courses/30/lessons/12927

// 시행착오
// 1. n 의 값 범위에 따라 단계별로 수행해야 함 -> 몫 갱신 이후, 나머지 갱신을 수행해야 정상동작함

#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;
using ll = long long;

void Print(const map<ll, ll, greater<>>& workmap)
{
    for (auto e : workmap)
    {
        cout << e.first << " " << e.second << endl;
    }
    cout << endl;
}

long long solution(int N, vector<int> works) 
{
    ll n = N;
    map<ll, ll, greater<>> workmap = { {0, 0} };

    for (ll w : works)
    {
        workmap[w] ++;
    }

    while (workmap.size() > 1 && n > 0)
    {
        //Print(workmap);
        auto it = begin(workmap);
        auto next = begin(workmap);
        next++;

        ll dis = it->first - next->first;
        ll cnt = it->second;
        ll val = dis * cnt;

        if (val <= n)
        {
            n -= val;
            workmap.erase(it);
            next->second += cnt;
        }
        else
        {
            if (n >= cnt)
            {
                ll a = it->first - (n / cnt);
                ll b = it->second;
                workmap.erase(it);
                workmap[a] += b;
                n %= cnt;
            }
            
            if(n > 0)
            {
                it->second -= n;
                workmap[it->first - 1] += n;
                n = 0;
            }            
        }
    }

    if (workmap.size() == 0)
        return 0;

    ll sum = 0;
    for (auto e : workmap)
    {
        sum += e.first * e.first * e.second;
    }

    return sum;
}


int main()
{
    //int n = 4;
    //vector<int> works = { 4, 3, 3 };

    //int n = 1;
    //vector<int> works = { 2, 1, 2 };

    //int n = 45;
    //vector<int> works = { 1, 2, 2, 3, 4, 6, 7, 7, 9, 9 };

    //int n = 3;
    //vector<int> works = { 1, 1 };

    int n = 99;
    vector<int> works = { 2, 15, 22, 55, 55 }; // ans = 580

    auto v = solution(n, works);
    cout << v << endl;


    return 0;
}