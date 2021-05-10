// bitmask

// bitmask를 활용하여 집합을 구현할 수 있다.
// 기업 목록의 선택지를 집합으로 표현해보자.


#include <iostream>
#include <bitset>
#include <string>
#include "Print.h"

using namespace std;

using uint64 = unsigned long long;
using uint8 = unsigned char;

// 해당 비트가 세팅되어 있는지 확인
bool IsBitSet(unsigned long long bit, int n)
{
    return (bit & ((unsigned long long)1) << n) > 0;
}

// 비트를 해석하여 집합에 포함된 원소 출력하기
void PrintSelections(const vector<string>& company, uint8 selections)
{
    vector<string> combs;
    for (int i = 0; i < company.size(); ++i)
    {
        if (IsBitSet(selections, i))
        {
            combs.push_back(company[i]);
        }
    }
    Print::Container(combs);
    cout << endl;
}

// 순회하며 카운팅해주는 방법 외의 특별한 다른 방법이 없음.
int CountBits(int n)
{
    int res = 0;
    for (; n; n >>= 1)
        res += n & 1;
    return res;
}


int main()
{

    // 기업 목록
    vector<string> company = { "Apple", "Google", "Amazon", "Facebook" };

    // 공집합
    {
        uint8 selections = 0;

        Print::Binary(selections);
    }

    // 전체집합 (모든 원소를 포함하는 집합)
    {
        uint8 selections = (1 << company.size()) - 1;

        PrintSelections(company, selections);
        Print::Binary(selections);
    }



    // 전체집합의 모든 부분집합 순회하기
    {
        for (int bit = 0; bit < (1 << company.size()); ++bit)
            //for (uint8 bit = 0; bit < (1 << company.size()); ++bit) // 값 오버플로우로 무한루프
        {
            // 출력
            PrintSelections(company, bit);
            Print::Binary<int, uint8>(bit);
        }
    }


    // 원소 추가
    {
        // 0번째 원소 
        uint8 selections = 0b00000001;

        // 3번째 원소 추가
        uint8 added = selections | (1 << 3);

        // 출력
        PrintSelections(company, selections);
        Print::Binary(selections);
        PrintSelections(company, added);
        Print::Binary(added);
    }


    // 원소의 포함여부 확인
    {
        uint8 selections = 0b00000010;
        int index = 1;
        if (IsBitSet(selections, index))
        {
            cout << company[index] << " is in set." << endl;
        }
    }

    // 원소 삭제
    {
        uint8 selections = 0b00001001;

        // 3번째 원소 제거
        uint8 deleted = selections & ~(1 << 3);

        // 출력
        PrintSelections(company, selections);
        Print::Binary(selections);
        PrintSelections(company, deleted);
        Print::Binary(deleted);
    }


    // 원소의 토글
    {
        uint8 selections = 0b00001000;

        for (int i = 0; i < 2; ++i)
        {
            // 3번째 원소 토글
            selections = selections ^ (1 << 3);

            // 출력
            PrintSelections(company, selections);
            Print::Binary(selections);
        }
    }

    // 집합의 크기 구하기
    {
        uint8 selections = 0b00001000;
        int count = CountBits(selections);

        cout << "set size : " << count << endl;
    }


    // 집합 연산
    {
        uint8 a = 0b00000011;
        uint8 b = 0b00000110;

        // 공집합
        uint8 empty = 0;

        // 전체집합
        uint8 universal = (1 << company.size()) - 1;

        // 합집합
        uint8 union_ab = (a | b);

        // 교집합
        uint8 intersection_ab = (a & b);

        // 차집합
        uint8 difference_ab = (a & b);

        // 대칭차집합
        uint8 symmetric_difference_ab = (a ^ b);

        // 여집합
        uint8 complement_a = (universal & (~a));

        Print::Binary(union_ab);
        Print::Binary(intersection_ab);
        Print::Binary(difference_ab);
        Print::Binary(symmetric_difference_ab);
        Print::Binary(complement_a);
    }


    // 최소 원소 가져오기
    // 음수 연산(2의 보수)을 활용한다.
    // (2의 보수는 모든 비트를 NOT연산한 후 1을 더한 값이다.)
    {
        uint8 selections = 0b00001010;
        uint8 val = (selections & -selections);

        cout << "selections\t: " << bitset<8>(selections) << endl;
        cout << "~selections\t: " << bitset<8>(~selections) << endl;
        cout << "~selections + 1\t: " << bitset<8>((~selections) + 1) << endl;
        cout << "-selections\t: " << bitset<8>(-selections) << endl << endl;
        Print::Binary(val);
    }

    // 최소 원소 지우기
    {
        uint8 selections = 0b00001010;
        uint8 val = (selections & (selections - 1));

        Print::Binary(val);
    }

    // 최소 원소 관련 연산들은 이후 최적화 자료구조 제작에 활용된다.
    // 펜윅트리, O(1)-우선순위 큐



    // 부분집합의 모든 부분집합 순회하기
    {
        // 부분집합 = {"Google", "Amazon", "Facebook"}
        uint8 selections = 0b00001110;

        for (int subset = selections; subset; subset = ((subset - 1) & selections))
        {
            PrintSelections(company, subset);
            Print::Binary<int, uint8>(subset);
        }

    }


    return 0;
}
