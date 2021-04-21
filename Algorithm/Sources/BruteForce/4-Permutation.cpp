// ����

// ���� ����1
// ����Լ��� ���� �˰��� ����
























#include <iostream>
#include <vector>
#include "Utility.h"
using namespace std;


// �޸𸮸� �̿��ϸ� ���� ���� �� �� ����
// 1���� N������ ������ ��� �ѹ��� �����غ�.
// i1�� ������ ���,
// i1�� ������ 1���� N������ ������ ��� �ѹ��� �����غ�.
// i2�� ������ ���,
// i1, i2�� ������ 1���� N������ ������ ��� �ѹ��� �����غ�.
// ...
const int kNum = 4;
bool selected[kNum + 1];

void Permutation(vector<int>& permutations)
{
    if (permutations.size() == kNum)
    {
        Print::Container(permutations);
    }

    for (int i = 1; i <= kNum; ++i)
    {
        if (!selected[i])
        {
            permutations.push_back(i);
            selected[i] = true;

            Permutation(permutations);

            permutations.pop_back();
            selected[i] = false;
        }
    }
}

void PermutationSTL()
{
    vector<int> permutations = { 1, 2, 3, 4 };

    do
    {
        Print::Container(permutations);

    } while (next_permutation(permutations.begin(), permutations.end()));
}

int main()
{
    vector<int> permutations;
    Permutation(permutations);

    cout << endl;

    PermutationSTL();

    return 0;
}

// next_permutation ������
// next_permutation�� ���� �����̳��� ���º��� ������ ����� ������,
// {1, 2, 3, 4, 5} �� �־��� ���� �������
// {5, 4, 3, 2, 1} �� �־��� ���� ������� �ٸ���.
// �̷��� ������ ���ڿ��� ������ ����� ���� �� ���� �߻��Ѵ�.
// "301", "103" �� �־��� �� ������ ���� �ٸ���.
// �̰� ���� ������ �ٶ��ٸ� ���� ������������ sort�� ���־�� �Ѵ�.