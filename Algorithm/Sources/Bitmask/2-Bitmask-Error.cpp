// bitmask
// 비트연산을 사용할 때, 문제가 되는 상황들

// 주의할 점
// 1. 항상 연산자 우선순위에 유의하여야 한다.
// 2. 상수 범위 오버플로우로 인한 문제
// 3. N-비트 크기의 변수를 N-비트 이상 시프트 연산하는 경우

#include <iostream>
#include <bitset>
using namespace std;

using uint8 = unsigned char;

int main()
{
    uint8 a = 0b10101000;

    // 연산자 우선순위로 인한 에러
    // 일반적으로 비트연산들은 일반연산보다 우선순위가 낮기 때문에,
    // 비트연산을 할 때에는 괄호를 습관화하는것이 좋다.
    int b = (a & a == a);
    int c = ((a & a) == a);
    cout << "(a & a == a)\t: " << b << endl;
    cout << "((a & a) == a)\t: " << c << endl << endl;



    // int 타입은 32비트를 이용하는 타입이기 때문에, 35번 시프트하는 연산은 이 타입에선 정의되어있지 않은 연산이다.
    // 또한 c++에서 상수 1은 32비트 부호있는 타입(int)을 이용하기 때문에, 같은 문제가 생길 수 있다.
    // 그러므로 캐스팅을 하거나 1LL 이라는 long long 타입 상수를 이용해주어야 한다.

    int test1 = 1 << 35;
    unsigned long long test2 = 1 << 35;
    unsigned long long test3 = (unsigned long long)1 << 35;
    //unsigned long long test3 = 1LL << 35;
    cout << "test1 : " << bitset<64>(test1) << endl;
    cout << "test2 : " << bitset<64>(test2) << endl;
    cout << "test3 : " << bitset<64>(test3) << endl << endl;




    return 0;
}
