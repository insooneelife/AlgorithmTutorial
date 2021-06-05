// 동전 2
// https://www.acmicpc.net/problem/2294

#include <iostream>
#include <algorithm>
#include <map>
#include <limits>
using namespace std;
typedef long long int ll;
const int BIG = numeric_limits<int>::max();

int coin[101];
map<int, ll> H;

ll f(int n, int k) 
{
    if (n == 0)
        return 0;

    if (n < 0)
        return BIG;

    auto it = H.find(n);
    if (it != H.end())
        return it->second;

    ll minv = BIG;
    for (int i = 0; i < k; i++) 
    {
        minv = min(minv, f(n - coin[i], k) + 1);
    }

    return H[n] = minv;
}

int main() 
{
    int n, k;
    cin >> k >> n;
    for (int i = 0; i < k; i++) 
    {
        cin >> coin[i];
    }
    ll gap = f(n, k);
    if (gap < BIG)
        cout << f(n, k);
    else
        cout << -1;
    return 0;
}