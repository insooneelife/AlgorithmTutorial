// ����Ž�� ����2
// ����ī �̷�
// https://www.acmicpc.net/problem/10448

// ������ ��� ����� ����?
// �ð����⵵?






















#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


// T(x) + T(y) + T(z) == n �� �����ϴ� ��� ����� ���� �˱� ����, 
// T(N) ������ N�� ������ �˾Ƴ����Ѵ�.
// ���� � T(N) > n �� N�� �����Ѵٸ�, N�� ������ �� ���� �Ѿ �ʿ䰡 ����.
// ���� T(100) = 100 * 101 / 2 = 5050 > K (3 <= K <= 1000) �̹Ƿ�,
// N�� 100���ε� ����ϴ�.
// N�� 100���� ��� ��� T(x)�� �̸� ����س���, ��� ������ ã�Ƽ� ���� ���� �� �ִ�.

const int kNum = 100;
int main()
{
    vector<int> tri;

    for (int i = 1; i <= kNum; ++i)
    {
        tri.push_back(i * (i + 1) / 2);
    }

    int t;
    cin >> t;

    while (t--)
    {

        int n;
        bool found = false;
        cin >> n;

        for (auto x : tri)
        {
            for (auto y : tri)
            {
                for (auto z : tri)
                {
                    if (x + y + z == n)
                    {
                        found = true;
                        break;
                    }
                }
            }
        }

        cout << (int)found << endl;
    }

    return 0;
}

// �����ؾ��ϴ� ���ܴ� ������ ������?