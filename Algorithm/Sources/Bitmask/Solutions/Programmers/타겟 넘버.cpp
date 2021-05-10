
// 타겟 넘버 (bitmask)
// https://programmers.co.kr/learn/courses/30/lessons/43165

#include <string>
#include <vector>
#include <bitset>
#include <iostream>
#include <cmath>

using namespace std;

bool IsBitSet(unsigned long long bit, int n)
{
    return (bit & ((unsigned long long)1) << n) > 0;
}

int solution(vector<int> numbers, int target) 
{
    unsigned int val = 1 << numbers.size();
    int answer = 0;

    for (int bit = 0; bit < val; ++bit)
    {
        int sum = 0;
        for (int j = 0; j < numbers.size(); ++j)
        {
            if (IsBitSet(bit, j))
                sum += numbers[j];
            else
                sum += numbers[j] * -1;
        }

        if (sum == target)
            answer++;
    }

    return answer;
}


int main()
{
    vector<int> numbers = { 1, 1, 1, 1, 1 };
    int target = 3;

    cout << solution(numbers, target);

    return 0;
}
