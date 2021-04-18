// 완전탐색 예제2
// 유레카 이론
// https://www.acmicpc.net/problem/10448

// 가능한 모든 경우의 수는?
// 시간복잡도?






















#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


// T(x) + T(y) + T(z) == n 이 성립하는 모든 경우의 수를 알기 위해, 
// T(N) 에서의 N의 범위를 알아내야한다.
// 만약 어떤 T(N) > n 인 N이 존재한다면, N의 범위는 그 위로 넘어갈 필요가 없다.
// 대충 T(100) = 100 * 101 / 2 = 5050 > K (3 <= K <= 1000) 이므로,
// N은 100으로도 충분하다.
// N을 100으로 잡고 모든 T(x)를 미리 계산해놓고, 모든 조합을 찾아서 답을 구할 수 있다.

const int kNum = 100;
int main()
{
    vector<int> tri;

    for (int i = 1; i <= kNum; ++i)
    {
        tri.push_back(i * (i + 1) / 2);
    }

    int t;
    cin >> t;

    while (t--)
    {

        int n;
        bool found = false;
        cin >> n;

        for (auto x : tri)
        {
            for (auto y : tri)
            {
                for (auto z : tri)
                {
                    if (x + y + z == n)
                    {
                        found = true;
                        break;
                    }
                }
            }
        }

        cout << (int)found << endl;
    }

    return 0;
}

// 주의해야하는 예외는 무엇이 있을까?