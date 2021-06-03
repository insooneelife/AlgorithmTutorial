
// 도둑질 (DP)
// https://programmers.co.kr/learn/courses/30/lessons/42897

// 스티커 모으기(2)   =>   동일 문제
// https://programmers.co.kr/learn/courses/30/lessons/12971

// 시행착오
// 1. 다음과 같이 오류 수정
//    수정 전, money[to] max(F(money, from, to - 2), F(money, from, to - 1));
//    수정 후, max(F(money, from, to - 2) + money[to], F(money, from, to - 1)); 

// 문제 풀이
// 원형의 경계부분에 대해 미리 경우를 나누어 해를 구한다.
// case 0. (0번째 값 선택o, (N - 1) 번째 값 선택x) -> 0번째 값을 더하고, 1번째 값과 (N - 1)번째 값을 선택하지 못하도록 한다.
// case 1. (0번째 값 선택x, (N - 1) 번째 값 선택o) -> (N - 1) 번째 값을 더하고, 0번째 값과 (N - 2)번째 값을 선택하지 못하도록 한다.
// case 2. (0번째 값 선택x, (N - 1) 번째 값 선택x) -> 1번째부터 N - 2번째 사이의 범위에서 자유롭게 선택

// 점화식
// F(N) : N개의 원소들을 선택하여 얻을 수 있는 가장 많은 돈
// F(N)
// N 위치의 값을 선택하는 경우 -> N - 1 위치는 선택할 수 없음 -> N - 2 위치부터 다시 선택 가능
// N 위치의 값을 선택하지 않는 경우 -> N - 1 위치부터 다시 선택 가능
// F(N) = max(F(N - 2) + money[N], F(N - 1))

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

ll mem[3][1000001] = { 0 };

ll F(const vector<int>& money, int from, int to)
{
    if (from > to)
        return 0;

    if (mem[from][to] > 0)
        return mem[from][to];

    return mem[from][to] = max(F(money, from, to - 2) + money[to], F(money, from, to - 1));
}

int solution(vector<int> money)
{
    const int N = money.size();
    ll case0 = money[0] + F(money, 2, N - 2);
    ll case1 = money[N - 1] + F(money, 1, N - 3);
    ll case2 = F(money, 1, N - 2);

    return max(case0, max(case1, case2));
}

int main()
{
    vector<int> money = { 1, 2, 3, 1 };
    cout << solution(money) << endl;

    return 0;
}