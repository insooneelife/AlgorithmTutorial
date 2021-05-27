// A
// https://www.acmicpc.net/problem/13171

// 시행착오
// 1. a, x 와 같은 인풋도 long long을 이용해야 함

#include <iostream>
using namespace std;
using ll = long long;

// (a * b) % m
static long long Mul(long long a, long long b)
{
    const static ll m = 1000000007LL;
    return ((a % m) * (b % m)) % m;
}

ll Pow(ll base, ll n)
{
    if (n == 0)
        return 1LL;

    if (n == 1)
        return base;

    if (n % 2 == 0)
    {
        ll val = Pow(base, n / 2);
        return Mul(val, val);
    }
    else
    {
        ll val = Pow(base, n / 2);
        return Mul(val, Mul(val, base));
    }
}

int main()
{
    ll a, x;
    cin >> a;
    cin >> x;

    cout << Pow(a, x);

    return 0;
}
