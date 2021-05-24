// 2 x n 타일링 (DP)
// https://programmers.co.kr/learn/courses/30/lessons/12900


#include <iostream>
#include <vector>
#include <string>

using namespace std;
using ll = long long;

class Modular
{
public:
    // (a + b) % m
    static long long Sum(long long a, long long b, long long m)
    {
        return ((a % m) + (b % m)) % m;
    }

    // (a - b) % m
    static long long Sub(long long a, long long b, long long m)
    {
        return ((a % m) - (b % m) + m) % m;
    }

    // (a * b) % m
    static long long Mul(long long a, long long b, long long m)
    {
        return ((a % m) * (b % m)) % m;
    }
};

ll mem[60001] = {};

ll F(int n)
{
    if (n == 1)
        return 1;
    if (n == 2)
        return 2;

    if (mem[n] > 0)
        return mem[n];

    return mem[n] = Modular::Sum(F(n - 1), F(n - 2), 1000000007);
}

int solution(int n)
{
    return F(n);
}


int main()
{
    int n = 4;
    int answer = solution(n);

    return 0;
}

