
// 줄 서는 방법 (분할정복)
// https://programmers.co.kr/learn/courses/30/lessons/12936

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

void Find(const vector<ll>& facts, vector<ll>& numbers, const ll k, ll n, vector<int>& out)
{
    if (n == 0)
        return;

    ll val = facts[n - 1];
    for (ll i = 1; i <= n; ++i)
    {
        if (k <= val * i)
        {
            ll temp = k - val * (i - 1);
            auto it = find(begin(numbers), end(numbers), numbers[i]);
            out.push_back(*it);
            numbers.erase(it);
            return Find(facts, numbers, temp, n - 1, out);
        }
    }
}

vector<int> solution(int n, long long k) 
{
    vector<ll> facts(21, 1);
    vector<ll> numbers(21, false);
    for (int i = 1; i <= 20; ++i)
    {
        facts[i] = facts[i - 1] * i;
        numbers[i] = i;

        cout << facts[i] << endl;
    }

    vector<int> answer;
    Find(facts, numbers, k, n, answer);

    return answer;
}

int main()
{
    int n = 3;
    int k = 5;

    solution(n, k);
    
    return 0;
}
