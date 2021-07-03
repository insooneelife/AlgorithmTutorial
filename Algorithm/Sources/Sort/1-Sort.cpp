// 기본 정렬

// plays 컨테이너 정렬하기
// 예제 1
// 기본 정렬

// 예제 2
// 내림차순 정렬

// 예제 3
// 정렬 람다

// 예제 4
// threshold 보다 크면 오름차순, 작거나 같으면 내림차순










#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

void Print(const vector<int>& v, string tag = "----------------------------")
{
    cout << tag << endl;
    for (auto e : v)
    {
        cout << e << " ";
    }
    cout << endl;
}

// sort에서 요구하는 operator< 를 함수로 구현
bool Compare(int a, int b)
{
    return a > b;
}

int main()
{
    vector<int> plays{ 3, 500, 2, 600, 5, 150, 800, 1, 2500, 800 };

    Print(plays, "--------------default-------------");

    // 기본, 오름차순
    sort(begin(plays), end(plays));

    // Compare 함수, 내림차순
    // sort(begin(plays), end(plays), Compare);

    // 람다, 내림차순
    // sort(begin(plays), end(plays), [](int a, int b) { return a > b; });

    // 기본, 반쪽만 정렬
    // sort(begin(plays) + plays.size() / 2, end(plays));
    // sort(begin(plays), begin(plays) + plays.size() / 2);

    // 람다, 값이 threshold 보다 크면 -> 내림차순, 작거나 같으면 오름차순, 큰 애들이 뒤로
    /*
    int threshold = 550;
    sort(begin(plays), end(plays), [threshold](int a, int b)
    {
        if (a > threshold && b > threshold)
        {
            return a > b;
        }
        else
        {
            return a < b;
        }
    });
    */

    Print(plays, "--------------sorted-------------");

    return 0;
}


// 정렬 문제 1
// K번째 수
// https://programmers.co.kr/learn/courses/30/lessons/42748