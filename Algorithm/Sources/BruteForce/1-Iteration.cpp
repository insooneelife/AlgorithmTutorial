// �ݺ���

// �ݺ��� ���� 1.
// �ݺ��� ����
// n�� 7�� ���, n���� ���� �� 4���� ���� ��� ��츦 ����ϴ� �˰���

#include <iostream>
using namespace std;

void CombIterate(int n)
{
    for (int x = 1; x <= n; ++x)
    {
        for (int y = x + 1; y <= n; ++y)
        {
            for (int z = y + 1; z <= n; ++z)
            {
                for (int w = z + 1; w <= n; ++w)
                {
                    cout << x << " " << y << " " << z << " " << w << endl;
                }
            }
        }
    }
}

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


int main()
{
    CombIterate(7);

    return 0;
}



// �ݺ��� ���� 2.
// �ϰ� ������
// https://www.acmicpc.net/problem/2309

// ������ ��� ����� ����?
// �ð����⵵?


// �ݺ��� ���� 3.
// �Ҽ� �����
// https://programmers.co.kr/learn/courses/30/lessons/12977

// ������ ��� ����� ����?
// �ð����⵵?


// ��Ī ���� ��ȣ
// for all x, P(x)
// ��� x�� ���� P(x)�� ���̴�.

// �����ܰ迡���� ��� ������ ������ ���̴� �ͺ���,
// ������ ���̽��� �� �ϳ��� ã�� ������ �����ϴ�.

// ���� ������ �����غ���.
// ��� x�� ����, x�� 5���� ũ��.
int All(vector<int> elements)
{
    for (int x : elements)
    {
        if (x <= 5)
            return false;
    }
    return true;
}



// ���� ���� ��ȣ
// there exists x, P(x)
// ��� �ϳ��� x�� ���� P(x)�� ���̴�.

// �����ܰ迡���� �� �״�� ������ �� �ִ�.

// ���� ������ �����غ���.
// ��� �ϳ��� x�� ���� x�� 5���� ũ��.

int Exists(vector<int> elements)
{
    for (int x : elements)
    {
        if (x > 5)
            return true;
    }
    return false;
}


// ex)
// ������ ��� ���յ� ��, ��� �ϳ��� ���տ� ����,
// ������ ��� ���� ���� ��찡 �����Ѵ�.

// ������ ��� ������ ��, ��� �ϳ��� ������ ����,
// ������ �� �� ��� �ϳ��� ���� ��찡 �����Ѵ�.












