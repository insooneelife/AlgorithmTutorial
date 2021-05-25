// 거스름돈
// https://programmers.co.kr/learn/courses/30/lessons/12907

// 문제풀이
// 0번째 money를 사용하여 거스름돈이 0이 되는 경우의 수 mem에 추가
// 1번째 money를 사용하여 거스름돈이 0이 되는 경우의 수 mem에 추가
// ..
// k - 1번째 money를 사용하여 거스름돈이 0이 되는 경우의 수 mem에 추가

// 시행착오
// 1. 메모리를 1000만 공간 잡는것이 시간초과를 일으키는 듯
// 2. 재귀함수가 과해지는 경우 stack overflow => segmantation fault (core dump)



#include <vector>
#include <iostream>
using namespace std;
using ll = long long;

static ll Sum(ll a, ll b, ll m)
{
    return ((a % m) + (b % m)) % m;
}

ll mem[100001] = { 0LL };
int solution(int n, vector<int> money)
{
    const int k = money.size();

    mem[0] = 1;
    for (int i = 0; i < k; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            if (j - money[i] >= 0)
                mem[j] = Sum(mem[j], mem[j - money[i]], 1000000007);
        }
    }
    return mem[n];
}


int main()
{
    int n = 5;
    vector<int> money = { 1,2,5 };

    auto answer = solution(n, money);
    cout << answer << endl;

    return 0;
}

