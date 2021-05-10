// bitmask
// 기본 연산

#include <iostream>
#include <bitset>
using namespace std;

using uint64 = unsigned long long;
using uint8 = unsigned char;

// 비트 출력
template <typename T>
void Print(T val, string tag = "val")
{
    cout << tag << endl;
    cout << bitset<sizeof(T) * 8>(val) << "   " << (uint64)val << endl << endl;
}

bool IsBitSet(unsigned long long bit, int n)
{
    return (bit & ((unsigned long long)1) << n) > 0;
}

int main()
{
    uint8 a = 0b10101001;
    uint8 b = 0b01010110;

    // 기본적인 비트연산
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


    // 2의 N승
    const int N = 3;
    uint8 bit = 1 << N;
    Print(bit, "2 ^ N");


    // N번째 비트가 켜져 있는지?
    uint8 testbit = 0b00011000;
    uint8 mask = 1 << N;
    bool isbitset = (testbit & mask) > 0;
    Print(testbit, "testbit");
    Print(mask, "testbit");
    Print(isbitset, "isbitset");


    // 어떤 숫자의 모든 비트를 순회하며 켜져있는지 확인
    uint8 num = 47;
    Print(num, "num");
    for (int i = 0; i < 8; ++i)
    {
        if (IsBitSet(num, i))
            cout << i << " true" << endl;
        else
            cout << i << " false" << endl;
    }

    return 0;
}
