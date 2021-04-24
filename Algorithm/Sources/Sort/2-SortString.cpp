// ���ڿ� ����

// ���� 1
// ù ���ĺ� ���� ����

// ���� 2
// 2�� vector�� ������ �����غ���
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

    // �⺻, ������ ��������
    //sort(begin(genres), end(genres));

    // ����, ������ ��������
    sort(begin(genres), end(genres), [](const string& a, const string& b) { return a > b; });

    //Print(genres, "--------------sorted-------------");

    // ����, ������ �������� �������� (����)
    sort(begin(genres), end(genres), [](const string& a, const string& b)
        {
            return lexicographical_compare(begin(a), end(a), begin(b), end(b), [](char a, char b)
                {
                    return a > b;
                });
        });

    // ����, ù ���ĺ�, ��������
    //sort(begin(genres), end(genres), [](const string& a, const string& b) { return a[0] > b[0]; });

    Print(genres, "--------------sorted-------------");

    return 0;
}


// ���� ���� 2
// ���� ū ��
// https://programmers.co.kr/learn/courses/30/lessons/42746

