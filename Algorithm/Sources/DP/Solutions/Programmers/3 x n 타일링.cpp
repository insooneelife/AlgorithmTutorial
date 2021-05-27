
// 문제해결
// 점화식 
// F(N) = 3 * F(N - 2) + 2 * F(N - 2) + 2 * F(N - 4) + ... + 2 * F(0)

// 누적합
// D[0] = 1                                                         Sum[0] = D[0]
// D[2] = D[0] + 2 * D[0]                                           Sum[2] = D[2] + D[0]
// D[4] = D[2] + 2 * D[2] + 2 * D[0]                                Sum[4] = D[4] + D[2] + D[0]
// D[6] = D[4] + 2 * D[4] + 2 * D[2] + 2 * D[0]                     Sum[6] = D[6] + D[4] + D[2] + D[0]
// ...
// D[N] = D[N - 2] + 2 * D[N - 2] + ... + 2 * D[2] + 2 * D[0]       Sum[N] = D[N] + D[N - 2] + ... + D[0]
// D[N] = D[N - 2] + 2 * Sum[N - 2]

// 시행착오
// 1. 메모이제이션 (시간초과) - 재귀로 인한 시간초과라 생각하고 배열로 변경
// 2. 배열 (시간초과) - O(N ^ 2)이 아닌 누적합을 이용한 O(N)으로 변경
// 3. 배열 + 누적합 (통과)

#include <iostream>
#include <string>
#include <vector>
using namespace std;
using ll = long long;

const ll mod = 1000000007;
static ll Sum(ll a, ll b)
{
    return ((a % mod) + (b % mod)) % mod;
}

static ll Mul(ll a, ll b)
{
    return ((a % mod) * (b % mod)) % mod;
}

ll d[5001] = { 0 };
ll sum[5001] = { 0 };
ll F(int n)
{
    sum[0] = d[0] = 1;
    for (int i = 2; i <= n; i += 2)
    {
        d[i] = Sum(d[i - 2], Mul(2, sum[i - 2]));
        sum[i] = Sum(d[i], sum[i - 2]);
    }

    return d[n];
}

int solution(int n)
{
    return F(n);
}

int main()
{
    int n = 4;

    cout << solution(n);

    return 0;
}


/*
// 메모이제이션 (시간초과)
ll mem[5001] = { 0 };
ll F(int n)
{
    if (n == 0)
        return 1LL;

    if (n % 2 == 1)
        return 0LL;

    if (n == 2)
        return 3LL;

    if (mem[n] != 0LL)
        return mem[n];

    ll sum = Mul(3, F(n - 2), mod);

    for (ll i = (ll)n - 4LL; i >= 0LL; i = i - 2LL)
    {
        sum = Sum(sum, Mul(2, F(i), mod), mod);
    }

    return mem[n] = sum;
}

*/

/*
// 배열 (시간초과)
ll d[5001] = { 0 };
ll F(int n)
{
    d[0] = 1;
    d[2] = 3;

    for (int i = 2; i <= n; ++i)
    {
        d[i] = Mul(3, d[i - 2]);
        for (int j = i - 4; j >= 0; j = j - 2)
        {
            d[i] = Sum(d[i], Mul(2, d[j]));
        }
    }

    return d[n];
}
*/