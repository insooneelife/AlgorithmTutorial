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


// 유효한 비교 함수 구현 규칙
// 1. a < a는 항상 거짓이다. (비반사성)
// 2. a < b가 참이면 b < a는 거짓이다. (비대칭성)
// 3. a < b가 참이고 b < c가 참이면 a < c 이다. (전이성)
// 4. a < b와 b < a가 모두 거짓이면 a와 b는 같은 값으로 간주한다.
//    a와 b가 같고, b와 c가 같으면 a와 c도 같다. (상등 관계의 전이성)

// 비반사성
bool Irreflexivity(int a, function<bool(int, int)> compare)
{
    return compare(a, a) == false;
}

// 비대칭성
bool Asymmetry(int a, int b, function<bool(int, int)> compare)
{
    bool result = compare(a, b);
    if (result)
    {
        return compare(b, a) == false;
    }
    // 가정이 거짓 => 참
    else
    {
        return true;
    }
}

// 전이성
bool Transistory(int a, int b, int c, function<bool(int, int)> compare)
{
    if (compare(a, b) && compare(b, c))
    {
        return compare(a, c) == true;
    }

    // 가정이 거짓 => 참
    return true;
}

// 상등 관계
bool Equivalence(int a, int b, function<bool(int, int)> compare)
{
    if (!compare(a, b) && !compare(b, a))
    {
        return (a == b) == true;
    }

    // 가정이 거짓 => 참
    return true;
}

// 상등 관계 전이성
bool EquivalenceTransistory(int a, int b, int c, function<bool(int, int)> compare)
{
    if (Equivalence(a, b, compare) && Equivalence(b, c, compare))
    {
        return Equivalence(a, c, compare) == true;
    }

    // 가정이 거짓 => 참
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

void CheckValid(int a, int b, int c)
{
    cout << "유효성 확인" << endl;

    // 비반사성
    {
        bool result1 = Irreflexivity(a, Compare1);
        bool result2 = Irreflexivity(a, Compare2);
        cout << "비반사성\nresult1 : " << result1 << "  result2 : " << result2 << endl << endl;
    }

    // 비대칭성
    {
        bool result1 = Asymmetry(a, b, Compare1);
        bool result2 = Asymmetry(a, b, Compare2);
        cout << "비대칭성\nresult1 : " << result1 << "  result2 : " << result2 << endl << endl;
    }

    // 전이성
    {
        bool result1 = Transistory(a, b, c, Compare1);
        bool result2 = Transistory(a, b, c, Compare2);
        cout << "전이성\nresult1 : " << result1 << "  result2 : " << result2 << endl << endl;
    }

    // 상등 관계
    {
        bool result1 = Equivalence(a, b, Compare1);
        bool result2 = Equivalence(a, b, Compare2);
        cout << "상등 관계\nresult1 : " << result1 << "  result2 : " << result2 << endl << endl;
    }

    // 상등 관계 전이성
    {
        bool result1 = EquivalenceTransistory(a, b, c, Compare1);
        bool result2 = EquivalenceTransistory(a, b, c, Compare2);
        cout << "상등 관계 전이성\nresult1 : " << result1 << "  result2 : " << result2 << endl << endl;
    }

    // STL 검사
    {
        bool result1 = CheckValidInSTL(a, b, Compare1);
        bool result2 = CheckValidInSTL(a, b, Compare2);
        cout << "STL 검사\nresult1 : " << result1 << "  result2 : " << result2 << endl << endl;
    }
}



int main()
{
    vector<int> numbers = { 5, 2, 1, 4, 5, 3, 9, 8 };

    CheckValid(5, 5, 1);

    // 예외가 발생함
    //sort(begin(numbers), end(numbers), Compare2);

    Print(numbers, "");

    return 0;
}

// int a = 1, b = 2;     a < b == true      a is less than b
// int a = 2, b = 1;     a < b == false     a is not less than b, because a is greater than b
// int a = 1, b = 1;     a < b == false     a is not less than b, because a equals b

// Returning true means you want a to be ordered before b.
// So return false if that is not the case, 
// either because you want b to be ordered before a, 
// or because their order doesn't matter.
// If you return true when the arguments are equal, 
// then you are saying that you want a to come before band you want b to come before a, which is a contradiction.