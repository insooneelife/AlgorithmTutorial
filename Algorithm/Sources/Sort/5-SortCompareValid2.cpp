// ���� ���� ��ȿ�� �������

// N���� ������ ���� ��, �� ���յ��� �����غ����� ����.
// ���ı�Ģ�� � ������ �ٸ� ������ �����Ѵٸ� �ڷ� ��ġ�ǵ��� �Ѵ�.


#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <algorithm>

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

// b�� a�� ���κ��������� Ȯ��
bool IsProperSubset(std::vector<int> a, std::vector<int> b)
{
    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());

    if (a == b) return false;

    return std::includes(a.begin(), a.end(), b.begin(), b.end());
}

bool Compare1(const vector<int>& a, const vector<int>& b)
{
    if (IsProperSubset(a, b))
        return false;

    if (IsProperSubset(b, a))
        return true;

    return true;
}

bool Compare2(const vector<int>& a, const vector<int>& b)
{
    if (IsProperSubset(a, b))
        return false;

    if (IsProperSubset(b, a))
        return true;

    return lexicographical_compare(begin(a), end(a), begin(b), end(b));
}

int main()
{
    vector<vector<int>> all = 
    {
        { 1, 2 },
        { 1, 2, 3, 4, 5, 6, 7 },
        { 2, 4, 7 },
        { 2, 4, 8 },
        { 1 },
        { 1, 2, 3, 4, 5, 6, 7, 8 }
    };

    cout << Compare1(all[0], all[2]) << " " << Compare1(all[2], all[0]);

    sort(begin(all), end(all), Compare1);
    
    for (const auto& v : all)
    {
        Print(v, "");
    }

    return 0;
}
