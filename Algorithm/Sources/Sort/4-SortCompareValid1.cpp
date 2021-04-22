// ���� ���� ��ȿ�� �������

// ���� ���Լ� �ۼ� �� ������Ȳ


#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;

void Print(const vector<int>& vec, string tag)
{
    cout << tag << endl;
    for (auto e : vec)
    {
        cout << e << " ";
    }
    cout << endl;
}

// operator<
bool Compare1(int a, int b)
{
    return a < b;
}

// ������ �ִ� ���Լ�
bool Compare2(int a, int b)
{
    if (a > b)
        return false;

    return true;
}

// STL������ �˻��� (_DEBUG_LT_PRED)
// ���Ī�� �˻縸 ��
bool CheckValidInSTL(int a, int b, function<bool(int a, int b)> compare)
{
    bool result = compare(a, b);
    if (result)
    {
        return !compare(b, a);
    }

    // ������ ���� => ��
    return true;
}


int main()
{
    vector<int> numbers = { 5, 2, 1, 4, 5, 3, 9, 8 };

    int a = 5;
    int b = 5;
    {
        bool result1 = CheckValidInSTL(a, b, Compare1);
        bool result2 = CheckValidInSTL(a, b, Compare2);
        cout << "��ݻ缺\nresult1 : " << result1 << "  result2 : " << result2 << endl << endl;
    }

    //sort(begin(numbers), end(numbers), Compare2);

    Print(numbers, "");

    return 0;
}

// ��ȿ�� �� �Լ� ���� ��Ģ
// 1. a < a�� �׻� �����̴�. (��ݻ缺)
// 2. a < b�� ���̸� b < a�� �����̴�. (���Ī��)
// 3. a < b�� ���̰� b < c�� ���̸� a < c �̴�. (���̼�)
// 4. a < b�� b < a�� ��� �����̸� a�� b�� ���� ������ �����Ѵ�.
//    a�� b�� ����, b�� c�� ������ a�� c�� ����. (��� ������ ���̼�)