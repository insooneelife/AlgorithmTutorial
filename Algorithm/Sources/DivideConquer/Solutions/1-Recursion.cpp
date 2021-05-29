
// 재귀 함수
// https://algorfati.tistory.com/134


#include<iostream>
using namespace std;

// [1,N]의 합을 재귀로 표현
int Sum(int n)
{
    if (n == 1)
        return 1;

    return Sum(n - 1) + n;
}

// 자명한 꼬리재귀
int SumTR(int n, int ans)
{
    if (n == 0)
        return ans;

    return SumTR(n - 1, n + ans);
}

// interface
int SumTR(int n)
{
    return SumTR(n, 0);
}

// 컴파일러 최적화가 가능한 꼬리재귀
int SumCompiler(int n)
{
    if (n == 1)
        return 1;

    return SumCompiler(n - 1) + n;
}


int main()
{
    cout << SumTR(10);

    return 0;
}



// 연습 문제 1.
// 재귀함수가 뭔가요?
// https://www.acmicpc.net/problem/17478