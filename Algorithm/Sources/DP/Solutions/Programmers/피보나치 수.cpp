// 피보나치 수
// https://programmers.co.kr/learn/courses/30/lessons/12945

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Modular
{
public:
    // (a + b) % m
    static int Sum(int a, int b, int m)
    {
        return ((a % m) + (b % m)) % m;
    }

    // (a - b) % m
    static int Sub(int a, int b, int m)
    {
        return ((a % m) - (b % m) + m) % m;
    }

    // (a * b) % m
    static int Mul(int a, int b, int m)
    {
        return ((a % m) * (b % m)) % m;
    }
};

int mem[100001] = {};

int solution(int n)
{
    if (n == 0)
        return 0;

    if (n == 1)
        return 1;

    if (mem[n] != 0)
        return mem[n];

    return mem[n] = Modular::Sum(solution(n - 1), solution(n - 2), 1234567);
}

int main()
{
    int n = 5;

    cout << solution(n);

    return 0;
}