
// 멀리 뛰기 (DP)
// https://programmers.co.kr/learn/courses/30/lessons/12914

#include <string>
#include <vector>
#include <iostream>

using namespace std;
using ll = long long;

ll mem[2001] = { 0 };
const ll mod = 1234567;

ll F(ll n)
{
    if (n == 0)
        return 1;

    if (n == 1)
        return 1;

    if (mem[n] != 0)
        return mem[n];

    return mem[n] = (F(n - 1) % mod + F(n - 2) % mod) % mod;
}


long long solution(int n)
{
    return F(n);
}

int main()
{
    int n = 5;
    cout << solution(n);


    return 0;
}