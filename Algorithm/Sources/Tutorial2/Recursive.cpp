// 재귀
// 재귀함수란?
// 기저조건
// 현재 문제를 부분문제로 재정의

// 재귀 예제1
// Sum 1 ~ N

// 재귀 예제2
// 재귀함수가 뭔가요?
// https://www.acmicpc.net/problem/17478




















#include <iostream>
#include <string>
using namespace std;

const string text[7] = 
{
    "어느 한 컴퓨터공학과 학생이 유명한 교수님을 찾아가 물었다.\n",
    "\"재귀함수가 뭔가요?\"\n",
    "\"잘 들어보게. 옛날옛날 한 산 꼭대기에 이세상 모든 지식을 통달한 선인이 있었어.\n",
    "마을 사람들은 모두 그 선인에게 수많은 질문을 했고, 모두 지혜롭게 대답해 주었지.\n",
    "그의 답은 대부분 옳았다고 하네. 그런데 어느 날, 그 선인에게 한 선비가 찾아와서 물었어.\"\n",
    "\"재귀함수는 자기 자신을 호출하는 함수라네\"\n",
    "라고 답변하였지.\n"
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

