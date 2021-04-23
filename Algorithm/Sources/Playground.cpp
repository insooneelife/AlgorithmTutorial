// Á¤¼ö »ï°¢Çü
// https://www.acmicpc.net/problem/1932

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