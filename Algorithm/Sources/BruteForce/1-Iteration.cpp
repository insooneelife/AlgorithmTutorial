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
// ����ī �̷�
// https://www.acmicpc.net/problem/10448

// ������ ��� ����� ����?
// �ð����⵵?
















