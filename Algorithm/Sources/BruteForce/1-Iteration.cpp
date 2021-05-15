// 반복문

// 1. 미지수와 순서쌍
// 두 자연수 n과 k에 대해 (1 <= n, k < 1000),
// 다음 식을 만족시키는 모든 순서쌍을 구하여라
// 2 * n * n - (k * k + 2) * n + (3 * k - 2) == 0


#include <iostream>
using namespace std;

void OrderedPair()
{
    for (int n = 1; n < 1000; ++n)
    {
        for (int k = 1; k < 1000; ++k)
        {
            if (2 * n * n - (k * k + 2) * n + (3 * k - 2) == 0)
            {
                cout << n << " " << k << endl;
            }
        }
    }
}

// 2. 반복문 조합
// n이 7인 경우, n개의 원소 중 4개를 고르는 모든 경우를 출력하는 알고리즘



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

// 3. 충돌 판정

struct Object
{
    Object(int x, int y, int r) : x(x), y(y), r(r) {}
    int x, int y, int r;
};

bool Collide(Object a, Object b)
{
    int distance = (b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y);
    return distance < ra + rb;
}

void CollideTest()
{

}


// 4. 한정 명제
// 전칭명제, 존재명제



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
// 카펫
// https://programmers.co.kr/learn/courses/30/lessons/42842


// 반복문 예제 4.
// 소수 만들기
// https://programmers.co.kr/learn/courses/30/lessons/12977

// 가능한 모든 경우의 수는?
// 시간복잡도?















