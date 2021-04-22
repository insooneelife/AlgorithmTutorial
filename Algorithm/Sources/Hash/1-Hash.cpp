// �ؽ� ���̺�(Hash Table)

// �ؽ� ���̺��̶�?
// key�� value ���·� �ڷḦ �����ϴ� �ڷᱸ��
// key�� ���ϼ��� ���� ���ڷ�, �ؽø� �ε����� ���� ���ȴ�.
// value�� ���� �����Ͱ� ����Ǵ� �����̴�.
// key�� ���� ������ ���ϴ� value�� �����ؿ� �� �ִ�.


// �ؽ� ���� 1.
// vector<int> inputs = { 50, 51, 51, 52, 51, 52, 51, 55, 54, 53, 52, 58, 59, 57 };
// �� ���� K�� ���� (50 <= K < 60)
// ������ ���� ��ǲ�� ���´ٰ� �������� �� �� ������ ������ ī�����ϴ� �˰����� �ۼ�.


#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <unordered_map>

using namespace std;


void HashExample()
{
    vector<int> inputs = { 50, 51, 51, 52, 51, 52, 51, 55, 54, 53, 52, 58, 59, 57 };

    // �ؽ� ���̺��� �ٿ��� �Ǵ� �޸𸮸� bucket�̶� �θ���.
    int bucket[10] = { 0 };
    int cnt_bucket[10] = { 0 };

    for (int i = 0; i < inputs.size(); ++i)
    {
        // �� �κ��� hash function�̴�.
        int index = inputs[i] % 50;
        bucket[index] = inputs[i];
        cnt_bucket[index]++;
    }

    for (int i = 0; i < 10; ++i)
    {
        cout << bucket[i] << " " << cnt_bucket[i] << endl;
    }
}


int main()
{
    HashExample();


    return 0;
}


// �ؽ� ����1
// �������� ���� ����
// https://programmers.co.kr/learn/courses/30/lessons/42576

// �ؽ� ����2
// ����
// https://programmers.co.kr/learn/courses/30/lessons/42578