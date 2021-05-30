
// [3차] 파일명 정렬 (정렬, 문자열)
// https://programmers.co.kr/learn/courses/30/lessons/17686

// stable_sort를 활용하여 문제 해결
// stable_sort는 비교대상이 아닌 항목들에 대해서는 이전 정렬상태를 유지한다.
// number 기준으로 정렬해도 최초에 인풋 순서가 유지된다.
// 그 상태에서 header 기준으로 정렬해도 number 기준 정렬상태와 인풋 순서 정렬상태가 유지된다.

#include <string>
#include <vector>
#include <algorithm>
//#include "Print.h"
using namespace std;

struct CharacterCase
{
    static void ToLowercase(std::string& str)
    {
        transform(begin(str), end(str), begin(str), [](char c)
            {
                if (IsUppercase(c))
                    return GetLowercase(c);
                return c;
            });
    }

    static void ToUppercase(std::string& str)
    {
        transform(begin(str), end(str), begin(str), [](char c)
            {
                if (IsLowercase(c))
                    return GetUppercase(c);
                return c;
            });
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

int FindNumIdx(const string& str)
{
    int idx = -1;
    for (int i = 0; i < str.size(); i++)
    {
        char c = str[i];
        if ('0' <= c && c <= '9')
        {
            idx = i;
            break;
        }
    }
    return idx;
}

int FindFirstNumber(const string& str, int& number)
{
    int idx = FindNumIdx(str);
    if (idx < 0)
        return idx;

    string num_and_str = str.substr(idx);
    number = stoi(num_and_str);

    return idx;
}

string GetHeader(const string& str)
{
    int idx = FindNumIdx(str);
    string header = str.substr(0, idx);
    CharacterCase::ToLowercase(header);
    return header;
}

vector<string> solution(vector<string> files) 
{
    stable_sort(begin(files), end(files), [](const string& a, const string& b)
        {
            int anumber;
            int bnumber;
            FindFirstNumber(a, anumber);
            FindFirstNumber(b, bnumber);
            return anumber < bnumber;
        });

    stable_sort(begin(files), end(files), [](const string& a, const string& b)
        {
            return GetHeader(a) < GetHeader(b);
        });

    return files;
}

int main()
{
    vector<string> files =
    {
        "img12.png", "img10.png", "img02.png", "img1.png", "IMG01.GIF", "img2.JPG"
    };
    /*1
    vector<string> files =
    {
        "F-5 Freedom Fighter", "B-50 Superfortress", "A-10 Thunderbolt II", "F-14 Tomcat"
    };
    */
    vector<string> v = solution(files);

    Print::Container(v);

    return 0;
}
