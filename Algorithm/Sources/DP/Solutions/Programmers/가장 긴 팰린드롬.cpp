// 가장 긴 팰린드롬 (DP)
// https://programmers.co.kr/learn/courses/30/lessons/12904


// 문제 풀이
// F(s, l) : s 위치로 시작하는 l길이의 부분문자열이 팰린드롬인지 판단

// 다음과 같은 길이 5의 문자열이 팰린드롬인지 판단하기 위해서, 
// 부분문제를 좌우 한칸씩 제거한 길이 3의 부분문자열로 놓는다.
// ■■■■■
// □■■■□
// 전체 문자열이 팰린드롬인지 판단은,
// (좌우가 제거된 부분 문자열이 팰린드롬이다) and (좌우 문자열이 같다) 로 정의할 수 있다.

// 점화식
// F(s, l) = F(s + 1, l - 2) & (str[s] == str[s + len - 1])


// 방법 1. 배열
// 시행착오
// 1. 길이가 작은 단위의 팰린드롬부터 판별해야 더 큰 팰린드롬을 성공적으로 판별할 수 있음
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


// 방법 2. 메모이제이션
// 시행착오
// 1. bool 판별을 위한 메모이제이션 배열을 이용하는 경우,
// 값이 true, false이기 때문에 null에 대한 표현을 해줄 방법이 없음.
// 그러므로 visited 배열을 통해, 메모이제이션이 진행되었는지 여부를 판단하도록 함.

// 2. 가장 긴 팰린드롬을 찾기 위해, 
// 팰린드롬 판단 후 다시 메모이제이션 배열을 순회하며 최대길이를 찾도록 하였는데,
// e가 s보다 작은 경우는 정의되지 않은 값이므로 길이를 찾는 과정에선 예외처리를 해주어야 한다.
// 하지만 재귀함수의 입장에서 (e - s < 0)인 경우는 기저 값을 만들어서 상위값의 재료로 이용되기 때문에 true로 리턴되어야 한다.

#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool visited[2500][2500] = { false };
bool mem[2500][2500] = { false };
bool Palindrome(const string& str, int s, int e)
{
    if (e - s <= 0)
        return mem[s][e] = true;

    if (visited[s][e])
        return mem[s][e];

    visited[s][e] = true;

    return mem[s][e] = (str[s] == str[e]) && Palindrome(str, s + 1, e - 1);
}

int solution2(string str)
{
    for (int i = 0; i < str.size(); ++i)
    {
        for (int j = i; j < str.size(); ++j)
        {
            Palindrome(str, i, j);
        }
    }

    int max_len = 0;
    for (int i = 0; i < str.size(); ++i)
    {
        for (int j = i; j < str.size(); ++j)
        {
            if (mem[i][j])
            {
                max_len = max(max_len, j - i + 1);
            }
        }
    }

    return max_len;
}