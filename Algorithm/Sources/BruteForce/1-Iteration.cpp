// 반복문

// 반복문 예제 1.
// 반복문 조합
// n이 7인 경우, n개의 원소 중 4개를 고르는 모든 경우를 출력하는 알고리즘

#include <iostream>
using namespace std;

void CombIterate(int n)
{
    for (int x = 1; x <= n; ++x)
    {
        for (int y = x + 1; y <= n; ++y)
        {
            for (int z = y + 1; z <= n; ++z)
            {
                for (int w = z + 1; w <= n; ++w)
                {
                    cout << x << " " << y << " " << z << " " << w << endl;
                }
            }
        }
    }
}

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


int main()
{
    CombIterate(7);

    return 0;
}



// 반복문 예제 2.
// 일곱 난쟁이
// https://www.acmicpc.net/problem/2309

// 가능한 모든 경우의 수는?
// 시간복잡도?




// 반복문 예제 3.
// 유레카 이론
// https://www.acmicpc.net/problem/10448

// 가능한 모든 경우의 수는?
// 시간복잡도?
















