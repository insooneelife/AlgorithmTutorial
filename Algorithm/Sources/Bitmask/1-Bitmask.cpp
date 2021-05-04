// bitmask

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
