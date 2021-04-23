// 정수 삼각형
// https://www.acmicpc.net/problem/1932


// 방법 1. 
// 배열
#include <iostream>
#include <string>
using namespace std;

const int N = 501;
int arr[501][501] = {};
int n;

int main()
{
    cin >> n;

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= i; ++j)
        {
            cin >> arr[i][j];
        }
    }

    for (int i = n; i >= 2; --i)
    {
        for (int j = i; j >= 2; --j)
        {
            arr[i - 1][j - 1] += max(arr[i][j], arr[i][j - 1]);
        }
    }

    cout << arr[1][1];

    return 0;
}


/*
// 방법 2.
// 메모이제이션
#include <iostream>
#include <string>
using namespace std;

const int N = 501;
int arr[501][501] = {};
int mem[501][501] = {};
int n;

int dp(int i, int j)
{
    if (n == i || n == j) return arr[i][j];

    if (mem[i][j] > 0) return mem[i][j];

    return mem[i][j] = arr[i][j] + max(dp(i + 1, j), dp(i + 1, j + 1));
}

int main()
{
    cin >> n;

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= i; ++j)
        {
            cin >> arr[i][j];
        }
    }

    int val = dp(1, 1);
    cout << val << endl;

    return 0;
}


*/