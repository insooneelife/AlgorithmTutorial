// ����ü ����

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
    // play ���� ��������
    bool operator<(const Data& other)
    {
        return play < other.play;
    }
};

// �⺻ ������å operator<
void SortByDefault(vector<Data>& vec)
{
    sort(begin(vec), end(vec));
}

// ���� ������å
// play ���� ��������
void SortByPlayDescending(vector<Data>& vec)
{
    sort(begin(vec), end(vec),
        [](const Data& a, const Data& b)
        {
            return a.play > b.play;
        });
}

// play ��������, name ���� ��������, index ���� ��������
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

// ���� ����3
// ����Ʈ�ٹ�
// https://programmers.co.kr/learn/courses/30/lessons/42579

