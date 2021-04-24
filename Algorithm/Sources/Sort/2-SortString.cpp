// 문자열 정렬

// 예제 1
// 첫 알파벳 기준 정렬

// 예제 2
// 2중 vector를 사전식 정렬해보기
/*
vector<vector<int>> all =
{
    { 1, 3 },
    { 1 },
    { 1, 2},
    { 1, 2, 3 },
    { 2, 1 },
    { 3, 2, 1 }
};

answer
1
1, 2
1, 2, 3
1, 3
2, 1
3, 2, 1
*/





#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

void Print(const vector<string>& v, string tag = "----------------------------")
{
    cout << tag << endl;
    for (auto e : v)
    {
        cout << e << endl;
    }
    cout << endl;
}

int main()
{
    vector<string> genres{ "zaa", "abc", "bac" "classicc", "pop", "classic", "pop", "pop", "classicc", "sga" };

    Print(genres, "--------------default-------------");

    // 기본, 사전식 오름차순
    //sort(begin(genres), end(genres));

    // 람다, 사전식 내림차순
    sort(begin(genres), end(genres), [](const string& a, const string& b) { return a > b; });

    //Print(genres, "--------------sorted-------------");

    // 람다, 사전식 내림차순 내림차순 (직접)
    sort(begin(genres), end(genres), [](const string& a, const string& b)
        {
            return lexicographical_compare(begin(a), end(a), begin(b), end(b), [](char a, char b)
                {
                    return a > b;
                });
        });

    // 람다, 첫 알파벳, 오름차순
    //sort(begin(genres), end(genres), [](const string& a, const string& b) { return a[0] > b[0]; });

    Print(genres, "--------------sorted-------------");

    return 0;
}


// 정렬 문제 2
// 가장 큰 수
// https://programmers.co.kr/learn/courses/30/lessons/42746

