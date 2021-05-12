// [1차] 비밀지도
// https://programmers.co.kr/learn/courses/30/lessons/17681

#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <bitset>
#include <algorithm>

using namespace std;

bool IsBitSet(unsigned long long bit, int n)
{
    return (bit & ((unsigned long long)1) << n) > 0;
}

vector<string> solution(int n, vector<int> arr1, vector<int> arr2)
{
    vector<string> answer;
    for (int i = 0; i < n; ++i)
    {
        int bit = (arr1[i] | arr2[i]);
        string m = "";

        for (int j = 0; j < n; ++j)
        {
            if(IsBitSet(bit, j))
                m += "#";
            else
                m += " ";
        }
        reverse(begin(m), end(m));
        answer.push_back(m);
    }

    return answer;
}