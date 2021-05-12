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
// 소수 만들기
// https://programmers.co.kr/learn/courses/30/lessons/12977

// 가능한 모든 경우의 수는?
// 시간복잡도?


// 전칭 한정 기호
// for all x, P(x)
// 모든 x에 대해 P(x)는 참이다.

// 구현단계에서는 모든 명제가 참임을 보이는 것보다,
// 거짓인 케이스를 단 하나만 찾는 방향이 간단하다.

// 다음 명제를 생각해보자.
// 모든 x에 대해, x는 5보다 크다.
int All(vector<int> elements)
{
    for (int x : elements)
    {
        if (x <= 5)
            return false;
    }
    return true;
}



// 존재 한정 기호
// there exists x, P(x)
// 적어도 하나의 x에 대해 P(x)는 참이다.

// 구현단계에서도 논리 그대로 적용할 수 있다.

// 다음 명제를 생각해보자.
// 적어도 하나의 x에 대해 x는 5보다 크다.

int Exists(vector<int> elements)
{
    for (int x : elements)
    {
        if (x > 5)
            return true;
    }
    return false;
}


// ex)
// 생성된 모든 조합들 중, 적어도 하나의 조합에 대해,
// 원소의 모든 값이 같은 경우가 존재한다.

// 생성된 모든 순열들 중, 적어도 하나의 순열에 대해,
// 원소의 값 중 적어도 하나가 같은 경우가 존재한다.












