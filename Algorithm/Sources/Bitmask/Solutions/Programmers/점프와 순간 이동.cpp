// 점프와 순간 이동 
// https://programmers.co.kr/learn/courses/30/lessons/12980

// 시행착오
// 1. BFS로 도전 (시간초과)

#include <bitset>
#include <iostream>
using namespace std;

int solution(int n)
{
    bitset<64> b(n);
    return b.count();
}

int main()
{
    int n = 5000;
    cout << solution(n);

    return 0;
}
