// ���
// ����Լ���?
// ��������
// ���� ������ �κй����� ������

// ��� ����1
// Sum 1 ~ N

// ��� ����2
// ����Լ��� ������?
// https://www.acmicpc.net/problem/17478




















#include <iostream>
#include <string>
using namespace std;

const string text[7] = 
{
    "��� �� ��ǻ�Ͱ��а� �л��� ������ �������� ã�ư� ������.\n",
    "\"����Լ��� ������?\"\n",
    "\"�� ����. �������� �� �� ����⿡ �̼��� ��� ������ ����� ������ �־���.\n",
    "���� ������� ��� �� ���ο��� ������ ������ �߰�, ��� �����Ӱ� ����� �־���.\n",
    "���� ���� ��κ� �ǾҴٰ� �ϳ�. �׷��� ��� ��, �� ���ο��� �� ���� ã�ƿͼ� ������.\"\n",
    "\"����Լ��� �ڱ� �ڽ��� ȣ���ϴ� �Լ����\"\n",
    "��� �亯�Ͽ���.\n"
};

const string base_indent = "____";

void Foo(int n, int k)
{
    if (n == k)
    {
        return;
    }

    string indent = "";
    for (int i = 0; i < k; ++i)
    {
        indent += base_indent;
    }

    if (k + 1 == n)
    {
        cout << indent + text[1];
        cout << indent + text[5];
    }
    else
    {
        for (int i = 1; i < 5; ++i)
        {
            cout << indent + text[i];
        }

        Foo(n, k + 1);
    }

    cout << indent + text[6];
}

int main()
{
    int n;
    cin >> n;

    cout << text[0];
    Foo(n + 1, 0);

    return 0;
}

