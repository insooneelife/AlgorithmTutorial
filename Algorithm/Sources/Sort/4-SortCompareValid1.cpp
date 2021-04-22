// 정렬 비교의 유효성 검증방법

// 정렬 비교함수 작성 시 문제상황


#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;

void Print(const vector<int>& vec, string tag)
{
    cout << tag << endl;
    for (auto e : vec)
    {
        cout << e << " ";
    }
    cout << endl;
}

// operator<
bool Compare1(int a, int b)
{
    return a < b;
}

// 문제가 있는 비교함수
bool Compare2(int a, int b)
{
    if (a > b)
        return false;

    return true;
}

// STL에서의 검사방법 (_DEBUG_LT_PRED)
// 비대칭성 검사만 함
bool CheckValidInSTL(int a, int b, function<bool(int a, int b)> compare)
{
    bool result = compare(a, b);
    if (result)
    {
        return !compare(b, a);
    }

    // 가정이 거짓 => 참
    return true;
}


int main()
{
    vector<int> numbers = { 5, 2, 1, 4, 5, 3, 9, 8 };

    int a = 5;
    int b = 5;
    {
        bool result1 = CheckValidInSTL(a, b, Compare1);
        bool result2 = CheckValidInSTL(a, b, Compare2);
        cout << "비반사성\nresult1 : " << result1 << "  result2 : " << result2 << endl << endl;
    }

    //sort(begin(numbers), end(numbers), Compare2);

    Print(numbers, "");

    return 0;
}

// 유효한 비교 함수 구현 규칙
// 1. a < a는 항상 거짓이다. (비반사성)
// 2. a < b가 참이면 b < a는 거짓이다. (비대칭성)
// 3. a < b가 참이고 b < c가 참이면 a < c 이다. (전이성)
// 4. a < b와 b < a가 모두 거짓이면 a와 b는 같은 값으로 간주한다.
//    a와 b가 같고, b와 c가 같으면 a와 c도 같다. (상등 관계의 전이성)