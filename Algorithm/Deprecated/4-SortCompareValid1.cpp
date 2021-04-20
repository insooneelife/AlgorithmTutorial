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


// ��ȿ�� �� �Լ� ���� ��Ģ
// 1. a < a�� �׻� �����̴�. (��ݻ缺)
// 2. a < b�� ���̸� b < a�� �����̴�. (���Ī��)
// 3. a < b�� ���̰� b < c�� ���̸� a < c �̴�. (���̼�)
// 4. a < b�� b < a�� ��� �����̸� a�� b�� ���� ������ �����Ѵ�.
//    a�� b�� ����, b�� c�� ������ a�� c�� ����. (��� ������ ���̼�)

// ��ݻ缺
bool Irreflexivity(int a, function<bool(int, int)> compare)
{
    return compare(a, a) == false;
}

// ���Ī��
bool Asymmetry(int a, int b, function<bool(int, int)> compare)
{
    bool result = compare(a, b);
    if (result)
    {
        return compare(b, a) == false;
    }
    // ������ ���� => ��
    else
    {
        return true;
    }
}

// ���̼�
bool Transistory(int a, int b, int c, function<bool(int, int)> compare)
{
    if (compare(a, b) && compare(b, c))
    {
        return compare(a, c) == true;
    }

    // ������ ���� => ��
    return true;
}

// ��� ����
bool Equivalence(int a, int b, function<bool(int, int)> compare)
{
    if (!compare(a, b) && !compare(b, a))
    {
        return (a == b) == true;
    }

    // ������ ���� => ��
    return true;
}

// ��� ���� ���̼�
bool EquivalenceTransistory(int a, int b, int c, function<bool(int, int)> compare)
{
    if (Equivalence(a, b, compare) && Equivalence(b, c, compare))
    {
        return Equivalence(a, c, compare) == true;
    }

    // ������ ���� => ��
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

void CheckValid(int a, int b, int c)
{
    cout << "��ȿ�� Ȯ��" << endl;

    // ��ݻ缺
    {
        bool result1 = Irreflexivity(a, Compare1);
        bool result2 = Irreflexivity(a, Compare2);
        cout << "��ݻ缺\nresult1 : " << result1 << "  result2 : " << result2 << endl << endl;
    }

    // ���Ī��
    {
        bool result1 = Asymmetry(a, b, Compare1);
        bool result2 = Asymmetry(a, b, Compare2);
        cout << "���Ī��\nresult1 : " << result1 << "  result2 : " << result2 << endl << endl;
    }

    // ���̼�
    {
        bool result1 = Transistory(a, b, c, Compare1);
        bool result2 = Transistory(a, b, c, Compare2);
        cout << "���̼�\nresult1 : " << result1 << "  result2 : " << result2 << endl << endl;
    }

    // ��� ����
    {
        bool result1 = Equivalence(a, b, Compare1);
        bool result2 = Equivalence(a, b, Compare2);
        cout << "��� ����\nresult1 : " << result1 << "  result2 : " << result2 << endl << endl;
    }

    // ��� ���� ���̼�
    {
        bool result1 = EquivalenceTransistory(a, b, c, Compare1);
        bool result2 = EquivalenceTransistory(a, b, c, Compare2);
        cout << "��� ���� ���̼�\nresult1 : " << result1 << "  result2 : " << result2 << endl << endl;
    }

    // STL �˻�
    {
        bool result1 = CheckValidInSTL(a, b, Compare1);
        bool result2 = CheckValidInSTL(a, b, Compare2);
        cout << "STL �˻�\nresult1 : " << result1 << "  result2 : " << result2 << endl << endl;
    }
}



int main()
{
    vector<int> numbers = { 5, 2, 1, 4, 5, 3, 9, 8 };

    CheckValid(5, 5, 1);

    // ���ܰ� �߻���
    //sort(begin(numbers), end(numbers), Compare2);

    Print(numbers, "");

    return 0;
}

// int a = 1, b = 2;     a < b == true      a is less than b
// int a = 2, b = 1;     a < b == false     a is not less than b, because a is greater than b
// int a = 1, b = 1;     a < b == false     a is not less than b, because a equals b

// Returning true means you want a to be ordered before b.
// So return false if that is not the case, 
// either because you want b to be ordered before a, 
// or because their order doesn't matter.
// If you return true when the arguments are equal, 
// then you are saying that you want a to come before band you want b to come before a, which is a contradiction.