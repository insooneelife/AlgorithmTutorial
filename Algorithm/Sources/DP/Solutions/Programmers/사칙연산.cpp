
// 사칙연산 (DP, MinMax)
// https://programmers.co.kr/learn/courses/30/lessons/1843

// 문제풀이
// 연산자 우선순위를 요구하는 점화식으로 행렬의 최소곱셈수 점화식과 형태는 동일하다.
// 점화식을 표현하기 위해 연산자와 피연산자 개념을 활용하자.
// 연산자는 반드시 어떤 두 피연산자를 필요로 한다.
// 즉, 연산자를 기준으로 왼쪽의 전부와, 오른쪽 전부를 각각 피연산자로 나눌 수 있다.

// 다음 예제를 보자
// 1 - 3 + 5 - 8
// 어떤 인덱스 k를 기준으로 왼쪽과 오른쪽을 쪼개는 경우의 수는 다음과 같다.

// k가 0인 경우,
// 1 - ((3 + 5) - 8) = 1
// 1 - (3 + (5 - 8)) = 1

// k가 1인 경우,
// (1 - 3) + (5 - 8) = -5

// k가 2인 경우,
// ((1 - 3) + 5) - 8 = -5
// (1 - (3 + 5)) - 8 = -15

// 또한 이 문제에서는 연산결과를 항상 최대로 가져가는것이 반드시 최적해가 된다고 보장할 수 없다.
// 최대값이 오히려 음수 연산자를 통해 최소값이 되어버릴수도 있기 때문이다.
// 그러므로, 연선결과중 최대값과 최소값을 모두 가져가고,
// 각 최대최소의 조합으로 나올 수 있는 모든 경우의 수를 부분문제로 두어야 할 것이다.

// 점화식
// F(i, j) = i위치부터 j위치까지의 연산결과의 최대값 and 최소값

// F(i, j) = 
// F(i, j) = for all k:              k 범위 [i, j - 1]
//     F(i, k)으로 얻은 최소값, 최대값
//     F(k + 1, j)으로 얻은 최소값, 최대값 
//     {최소, 최소}, {최소, 최대}, {최대, 최소}, {최대, 최대} 조합들 중 현재의 최소, 최대 반환
// 


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