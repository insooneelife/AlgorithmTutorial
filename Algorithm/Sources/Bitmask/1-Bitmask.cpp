// bitmask

// 1. 매우 빠른 시간에 동작한다.
// 2. 간결하게 코드를 작성할 수 있다.
// 3. 메모리 절약이 가능하다.
// 4. 중첩 컨테이너를 단순 컨테이너로 대체할 수 있다.
// ex) map<vector<bool>, int>  ->  vector<int>
// 5. 집합 개념으로 활용될 수 있고, 집합 연산(합집합, 교집합, 차집합 ..)이 가능하다.
// 6. 어떤 원소들에 대한 모든 조합을 표현하기에 아주 편리하다.

// 주의할 점
// 1. 항상 연산자 우선순위에 유의하여야 한다.
// 2. 상수 범위 오버플로우로 인한 문제
// 3. 부호 있는 타입을 이용하는 경우의 문제
// 4. N-비트 크기의 변수를 N-비트 이상 시프트 연산하는 경우


#include <iostream>
#include <bitset>
using namespace std;

using uint64 = unsigned long long;
using uint8 = unsigned char;

template <typename T>
void Print(T val, string tag = "val")
{
    cout << tag << endl;
    cout << bitset<sizeof(T) * 8>(val) << "   " << (uint64)val << endl << endl;
}

int main()
{
    uint8 a = 0b10101001;
    uint8 b = 0b01010110;

    uint8 bit_and = a & b;
    uint8 bit_or = a | b;
    uint8 bit_xor = a ^ b;
    uint8 bit_not = ~a;
    uint8 bit_shift_left = a << 1;
    uint8 bit_shift_right = a >> 1;

    Print(a, "a");
    Print(b, "b");

    Print(bit_and, "a and b");
    Print(bit_or, "a or b");
    Print(bit_xor, "a xor b");
    Print(bit_not, "not a");
    Print(bit_shift_left, "shift left a 1");
    Print(bit_shift_right, "shift right a 1");




    /*
    uint8_t a = 0b01101110;
    uint8_t b = 0b01111110;

    if ((a & b) == a)
    {
        cout << bitset<8>(a & b);
    }
    */

    return 0;
}
