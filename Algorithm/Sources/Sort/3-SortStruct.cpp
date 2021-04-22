// 구조체 정렬

#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <algorithm>

using namespace std;

struct Data
{
    string name;
    int play;
    int i;

    Data() : name(0), play(0), i(0) {}

    Data(string name, int play, int i) : name(name), play(play), i(i) {}

    // for default
    // play 기준 오름차순
    bool operator<(const Data& other)
    {
        return play < other.play;
    }
};

// 기본 정렬정책 operator<
void SortByDefault(vector<Data>& vec)
{
    sort(begin(vec), end(vec));
}

// 람다 정렬정책
// play 기준 내림차순
void SortByPlayDescending(vector<Data>& vec)
{
    sort(begin(vec), end(vec),
        [](const Data& a, const Data& b)
        {
            return a.play > b.play;
        });
}

// play 오름차순, name 기준 오름차순, index 기준 오름차순
void SortByPlayToNameAndIndexAscending(vector<Data>& vec)
{
    sort(begin(vec), end(vec),
        [](const Data& a, const Data& b)
        {
            if (a.play == b.play)
            {
                if (a.name == b.name)
                {
                    return a.i < b.i;
                }

                return a.name < b.name;
            }

            return a.play < b.play;
        });
}

void Print(const vector<Data>& v, string tag = "----------------------------")
{
    cout << tag << endl;
    for (auto e : v)
    {
        cout << e.name << " " << e.play << " " << e.i << endl;
    }
    cout << endl;
}

int main()
{
    vector<string> genres{ "classicc", "pop", "classic", "classic", "pop", "pop" };
    vector<int> plays{ 500, 600, 150, 800, 2500, 800 };
    vector<Data> vec;

    for (int i = 0; i < plays.size(); ++i)
    {
        vec.push_back(Data(genres[i], plays[i], i));
    }

    Print(vec, "--------------default-------------");

    SortByDefault(vec);

    Print(vec, "--------------sorted-------------");

    return 0;
}

// 정렬 예제3
// 베스트앨범
// https://programmers.co.kr/learn/courses/30/lessons/42579

