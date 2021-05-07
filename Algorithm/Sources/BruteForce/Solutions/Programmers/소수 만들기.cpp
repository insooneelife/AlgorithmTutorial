
// 소수 만들기
// https://programmers.co.kr/learn/courses/30/lessons/12977

#include <vector>
#include <iostream>
#include <cmath>
using namespace std;

static bool IsPrime(int n)
{
    if (n <= 1)
        return false;

    // 2는 예외
    if (n == 2)
        return true;

    // 모든 짝수는 2의 배수니까 소수 x
    if (n % 2 == 0)
        return false;

    // 3 5 7 9 ...
    int sqrtn = (int)(sqrt(n));
    for (int i = 3; i <= sqrtn; i += 2)
    {
        if (n % i == 0)
        {
            return false;
        }
    }
    return true;
}

int solution(vector<int> nums)
{
    int answer = 0;

    for (int i = 0; i < nums.size(); ++i)
        for (int j = i + 1; j < nums.size(); ++j)
            for (int k = j + 1; k < nums.size(); ++k)
                if (IsPrime(nums[i] + nums[j] + nums[k]))
                    answer++;
    return answer;
}