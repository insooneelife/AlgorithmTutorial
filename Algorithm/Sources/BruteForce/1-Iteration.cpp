// �ݺ���

// 1. �������� ������
// �� �ڿ��� n�� k�� ���� (1 <= n, k < 1000),
// ���� ���� ������Ű�� ��� �������� ���Ͽ���
// 2 * n * n - (k * k + 2) * n + (3 * k - 2) == 0


#include <iostream>
using namespace std;

void OrderedPair()
{
    for (int n = 1; n < 1000; ++n)
    {
        for (int k = 1; k < 1000; ++k)
        {
            if (2 * n * n - (k * k + 2) * n + (3 * k - 2) == 0)
            {
                cout << n << " " << k << endl;
            }
        }
    }
}

// 2. �ݺ��� ����
// n�� 7�� ���, n���� ���� �� 4���� ���� ��� ��츦 ����ϴ� �˰���



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

// 3. �浹 ����

struct Object
{
    Object(int x, int y, int r) : x(x), y(y), r(r) {}
    int x, int y, int r;
};

bool Collide(Object a, Object b)
{
    int distance = (b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y);
    return distance < ra + rb;
}

void CollideTest()
{

}


// 4. ���� ����
// ��Ī����, �������



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
// ī��
// https://programmers.co.kr/learn/courses/30/lessons/42842


// �ݺ��� ���� 4.
// �Ҽ� �����
// https://programmers.co.kr/learn/courses/30/lessons/12977

// ������ ��� ����� ����?
// �ð����⵵?















