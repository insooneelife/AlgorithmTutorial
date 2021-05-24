// 가장 긴 팰린드롬 (DP)
// https://programmers.co.kr/learn/courses/30/lessons/12904


#include <iostream>
#include <string>
#include <vector>
using namespace std;

void Palindrome(const string& str, vector<vector<bool>>& mem)
{
    mem.resize(str.size(), vector<bool>(str.size() + 1, false));

    // 길이 0, 1, 2 palindrome 전처리
    for (int s = 0; s < str.size(); ++s)
    {
        mem[s][0] = false;
        mem[s][1] = true;
        if (s + 1 < str.size())
            mem[s][2] = str[s] == str[s + 1];
    }

    // 길이 3 palindrome 판별
    // 길이 4 palindrome 판별
    // ...
    // 길이 N palindrome 판별
    for (int len = 3; len <= str.size(); ++len)
    {
        for (int s = 0; s + len - 1 < str.size(); ++s)
        {
            mem[s][len] = mem[s + 1][len - 2] && (str[s] == str[s + len - 1]);
        }
    }
}


int solution(string str)
{
    vector<vector<bool>> mem;
    Palindrome(str, mem);
    
    int max_len = 0;
    for (int i = 0; i < str.size(); ++i)
    {
        for (int j = 0; j <= str.size(); ++j)
        {
            if (mem[i][j])
            {
                max_len = max(max_len, j);
            }
        }
    }

    return max_len;
}


int main()
{
    //string str = "abcdefgh";
    string str = "abcdcba";
    //string str = "abacde";
    int answer = solution(str);

    cout << answer << endl;

    return 0;
}

