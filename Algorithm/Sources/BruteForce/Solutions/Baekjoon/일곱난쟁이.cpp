// 일곱난쟁이 (Brute Force)
// https://www.acmicpc.net/problem/2309

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 7명의 합 = 100
// 9명의 합 = 100 + x + y
// N <= 9 이므로 순서쌍 (x, y)의 가능한 모든 경우의 수는 C(9, 2) = 36가지이다.
const int kNum = 9;

int main()
{
    vector<int> v(kNum);
    int sum = 0;

    for (int i = 0; i < kNum; ++i)
    {
        cin >> v[i];
        sum += v[i];
    }

    int not1 = v[0];
    int not2 = v[1];

    for (int x = 0; x < kNum; ++x)
    {
        for (int y = x + 1; y < kNum; ++y)
        {
            if (sum - (v[x] + v[y]) == 100)
            {
                not1 = v[x];
                not2 = v[y];

                break;
            }
        }
    }

    vector<int> real;
    for (auto e : v)
    {
        if (e != not1 && e != not2)
        {
            real.push_back(e);
        }
    }

    sort(begin(real), end(real));

    for (auto e : real)
    {
        cout << e << endl;
    }

    return 0;
}