
// 이항 계수 (선택에 대한 점화식)
// n개의 원소에서 k개를 선택하는 경우의 수

// nCk
// 4C2 = 6

// 4C2
// 1 2 3 4
// o            3C1
// x            3C2 

// nCk
// (n - 1) C (k - 1)
// (n - 1) C k

// n번째 선택에서 n번 원소를 선택하는 경우
// n번째 선택에서 n번 원소를 선택하지 않는 경우

#include <iostream>
#include <string>
#include <vector>
using namespace std;

int mem[500][100] = { 0 };
int Bino(int n, int k)
{
    if (k == 0)
        return 1;

    if (n == k)
        return 1;

    if (mem[n][k] != 0)
        return mem[n][k];

    return mem[n][k] = Bino(n - 1, k) + Bino(n - 1, k - 1);
}



int main()
{
    cout << Bino(4, 2);

    return 0;
}


// 예제 문제
// 동전 1.
// https://www.acmicpc.net/problem/2293