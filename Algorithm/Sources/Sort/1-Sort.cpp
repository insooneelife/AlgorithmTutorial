// �⺻ ����

// plays �����̳� �����ϱ�
// ���� 1
// �⺻ ����

// ���� 2
// �������� ����

// ���� 3
// ���� ����

// ���� 4
// threshold ���� ũ�� ��������, �۰ų� ������ ��������










#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

void Print(const vector<int>& v, string tag = "----------------------------")
{
    cout << tag << endl;
    for (auto e : v)
    {
        cout << e << " ";
    }
    cout << endl;
}

// sort���� �䱸�ϴ� operator< �� �Լ��� ����
bool Compare(int a, int b)
{
    return a > b;
}

int main()
{
    vector<int> plays{ 3, 500, 2, 600, 5, 150, 800, 1, 2500, 800 };

    Print(plays, "--------------default-------------");

    // �⺻, ��������
    sort(begin(plays), end(plays));

    // Compare �Լ�, ��������
    // sort(begin(plays), end(plays), Compare);

    // ����, ��������
    // sort(begin(plays), end(plays), [](int a, int b) { return a > b; });

    // �⺻, ���ʸ� ����
    // sort(begin(plays) + plays.size() / 2, end(plays));
    // sort(begin(plays), begin(plays) + plays.size() / 2);

    // ����, ���� threshold ���� ũ�� -> ��������, �۰ų� ������ ��������, ū �ֵ��� �ڷ�
    /*
    int threshold = 550;
    sort(begin(plays), end(plays), [threshold](int a, int b)
    {
        if (a > threshold && b > threshold)
        {
            return a > b;
        }
        else
        {
            return a < b;
        }
    });
    */

    Print(plays, "--------------sorted-------------");

    return 0;
}


// ���� ���� 1
// K��° ��
// https://programmers.co.kr/learn/courses/30/lessons/42748