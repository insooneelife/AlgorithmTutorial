
// 분할정복
// https://algorfati.tistory.com/133

// Fast Power


#include <iostream>
using namespace std;

/*
// O(P)
int Pow(int n, int p)
{
    int ret = 1;
    for (int i = 0; i < p; ++i)
    {
        ret *= n;
    }
    return ret;
}
*/

// O(logP)
int Pow(int n, int p)
{
    if (p == 0)
        return 1;

    if (p == 1)
        return n;

    if (p % 2 == 0)
    {
        int val = Pow(n, p / 2);
        return val * val;
    }
    else
    {
        int val = Pow(n, p / 2);
        return val * val * n;
    }
}


int main()
{
    cout << Pow(2, 3);

    return 0;
}


// 연습 문제 1.
// A
// https://www.acmicpc.net/problem/13171

// 연습 문제 2.
// 행렬 제곱
// https://www.acmicpc.net/problem/10830