
// [1차] 뉴스 클러스터링
// https://programmers.co.kr/learn/courses/30/lessons/17677

// 시행착오
// 1. a.size() == 0 && b.size() == 0 인 경우 예외처리 시에도 65536를 곱해줘야 함.

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
//#include "Utility.h"
//#include "Print.h"


using namespace std;

struct Utility
{
    static void ToLowercase(std::string& str)
    {
        for (char& c : str)
        {
            if (IsUppercase(c))
            {
                c = GetLowercase(c);
            }
        }
    }

    static void ToUppercase(std::string& str)
    {
        for (char& c : str)
        {
            if (IsLowercase(c))
            {
                GetUppercase(c);
            }
        }
    }

    static bool IsLowercase(char c)
    {
        return 'a' <= c && c <= 'z';
    }

    static bool IsUppercase(char c)
    {
        return 'A' <= c && c <= 'Z';
    }

    static char GetLowercase(char c)
    {
        return c - 'A' + 'a';
    }

    static char GetUppercase(char c)
    {
        return c - 'a' + 'A';
    }
};



vector<string> MakeSet(string str)
{
    vector<string> vec;

    for (int i = 0; i < str.size() - 1; ++i)
    {
        if (Utility::IsLowercase(str[i]) &&
            Utility::IsLowercase(str[i + 1]))
        {
            string s = "";
            s += str[i];
            s += str[i + 1];
            vec.push_back(s);
        }
    }

    return vec;
}


int solution(string str1, string str2)
{
    Utility::ToLowercase(str1);
    Utility::ToLowercase(str2);

    vector<string> v1 = MakeSet(str1);
    vector<string> v2 = MakeSet(str2);

    sort(begin(v1), end(v1));
    sort(begin(v2), end(v2));

    vector<string> a;
    set_intersection(begin(v1), end(v1), begin(v2), end(v2), back_inserter(a));

    vector<string> b;
    set_union(begin(v1), end(v1), begin(v2), end(v2), back_inserter(b));

    float val = 0.0f;
    if (a.size() == 0 && b.size() == 0)
    {
        val = 1;
    }
    else
    {
        val = (float)a.size() / (float)b.size();
    }

    val *= 65536;

    return val;
}