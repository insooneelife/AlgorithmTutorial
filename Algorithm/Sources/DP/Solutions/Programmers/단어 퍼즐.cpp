// 단어 퍼즐 (DP)
// https://programmers.co.kr/learn/courses/30/lessons/12983

// 시행착오
// 1. t 문자열의 길이 범위를 잘못 확인함

#include <iostream>
#include <string>
#include <vector>
using namespace std;
using ll = long long;

const int MAX = numeric_limits<int>::max();
ll mem[20001] = { 0 };

bool MatchBackward(const string& str, int n, const string& sub)
{
    int size = sub.size();
    for (int j = 0; j < size; ++j)
    {
        if (sub[j] != str[n - size + j])
        {
            return false;
        }
    }
    return true;
}

ll F(const vector<string>& strs, string& t, int n)
{
    if (n < 0)
        return MAX;

    if (n == 0)
        return 0;

    if (mem[n] > 0)
        return mem[n];

    ll minv = MAX;

    for (int i = 0; i < strs.size(); ++i)
    {
        int size = strs[i].size();
        if (n - size < 0)
            continue;

        if (MatchBackward(t, n, strs[i]))
        {
            minv = min(minv, F(strs, t, n - size) + 1LL);
        }
    }

    return mem[n] = minv;
}

int solution(vector<string> strs, string t)
{
    for (int i = 0; i < 20001; ++i)
        mem[i] = 0;

    ll val = F(strs, t, t.size());
    return val >= MAX ? -1 : val;
}



int main()
{
    //vector<string> strs = {"ba", "na", "n", "a"};
    //string t = "banana";

    //vector<string> strs = { "app","ap","p","l","e","ple","pp" };
    //string t = "apple";

    vector<string> strs = { "ba","an","nan","ban","n" };
    string t = "banana";

    cout << solution(strs, t);

    return 0;
}


