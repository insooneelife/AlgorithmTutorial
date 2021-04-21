#pragma once


#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include "Utility.h"

class STL
{
public:

    // sort
    // ���ĵ� �����̳ʸ� ��ȯ�Ѵ�.
    static void Sort()
    {
        using namespace std;

        vector<int> numbers = { 3, 2, 1, 5, 4 };
        sort(begin(numbers), end(numbers));

        Print::Container(numbers);
    }

    // find
    // Ư�� ���Ҹ� ã��, �� ������ �ݺ��ڸ� ��ȯ�Ѵ�.
    static void Find()
    {
        using namespace std;

        vector<int> numbers = { 3, 2, 1, 5, 4 };
        auto it = find(begin(numbers), end(numbers), 3);

        cout << *it << endl;
    }

    // erase
    // �ݺ��ڸ� ���ڷ� �޾� �� �ݺ��� ��ġ�� ���Ҹ� �����Ѵ�.
    // find�� ���� ����ϸ� Ư�� ���Ҹ� ������ �� �ִ�.
    static void Erase()
    {
        using namespace std;

        vector<int> numbers = { 1, 3, 2, 3, 1, 5, 4, 5 };
        auto it = find(begin(numbers), end(numbers), 3);
        numbers.erase(it);

        Print::Container(numbers);
    }

    // erase range
    // �ݺ��� �ΰ��� ���ڷ� �޾� �� �ݺ��ڵ� ������ ��� ���Ҹ� �����Ѵ�.
    static void EraseRange()
    {
        using namespace std;

        vector<int> numbers = { 1, 3, 2, 3, 1, 5, 4, 5 };
        numbers.erase(begin(numbers) + 1, begin(numbers) + 4);

        Print::Container(numbers);
    }


    // unique
    // �ߺ��� ���ҵ��� ��� �ڷ� ������, �ߺ����ҵ��� ���� �ݺ��ڸ� ��ȯ�Ѵ�.
    // �����̳ʰ� ���ĵ� ���¿��� �������Ѵ�.
    // �ߺ����Ҹ� �����̳ʿ��� ��� �����Ϸ��� ������ ���� erase�� ���� ����ϸ� �ȴ�.
    static void Unique()
    {
        using namespace std;

        vector<int> numbers = { 1, 3, 2, 3, 1, 5, 4, 5 };

        sort(begin(numbers), end(numbers));
        auto it = unique(begin(numbers), end(numbers));
        numbers.erase(it, end(numbers));

        Print::Container(numbers);
    }

    // max_element, min_element
    // �����̳� ���� �ִ� ���ҿ�, �ּ� ������ �ݺ��ڸ� ��ȯ�Ѵ�.
    static void MinMaxElement()
    {
        using namespace std;

        vector<int> v = { 1, 2, 3, 4, 5 };
        int max_val = *max_element(begin(v), end(v));
        int min_val = *min_element(begin(v), end(v));
        cout << max_val << " " << min_val;
    }

    // set_difference
    // �����̳ʿ��� �ٸ� �����̳��� ��� ���Ҹ� ������ ���ο� �����̳ʸ� ��ȯ�Ѵ�.
    // �Ϲ� �����̳��� ��� ���Ұ� ���ĵ� ���¿��� �Ѵ�.
    static void SetDifference()
    {
        using namespace std;

        vector<int> v = { 1, 2, 3, 4, 5 };
        vector<int> u = { 1, 3, 5 };
        vector<int> output;
        set_difference(begin(v), end(v), begin(u), end(u), std::back_inserter(output));

        Print::Container(v);
    }

    // �����̳��� ������ �ٸ����� �����ϴ�.
    static void SetDifference_VectorToSet()
    {
        using namespace std;

        vector<int> v = { 1, 2, 3, 4, 5 };
        set<int> u = { 1, 3, 5 };
        vector<int> output;
        set_difference(begin(v), end(v), begin(u), end(u), std::back_inserter(output));

        Print::Container(v);
    }

    // includes
    // �� �����̳ʰ� �ٸ� �����̳��� �κ��������� Ȯ���Ѵ�.
    // �����̳ʰ� ���ĵ� ���¿��� �������Ѵ�.
    // �κ����� Ȯ���Լ�
    static void Includes()
    {
        using namespace std;

        vector<int> a = { 1, 2, 3, 4, 5 };
        vector<int> b = { 1, 3, 5 };

        std::sort(begin(a), end(a));
        std::sort(begin(b), end(b));
        
        bool does_includes = std::includes(a.begin(), a.end(), b.begin(), b.end());

        cout << does_includes << endl;
    }


    // next_permutation
    // �����̳��� ���� ������ ��ȯ�Ѵ�.
    // ������ ���� ������� ��� ������ ����� �� �ִ�.
    static void NextPermutation()
    {
        using namespace std;

        std::vector<int> vec{ 1, 2, 3, 4, 5 };

        do
        {
            Print::Container(vec);

        } while (next_permutation(vec.begin(), vec.end()));
    }

    // ������ ����, ���� ���¸� �������� ���� ������ ��ȯ�ϱ� ������,
    // ��� ������ ��ȸ�ϱ⸦ ����ϸ� ����Ѵٸ� ��ǲ�� ���� ���¸� Ȯ���ؾ��Ѵ�.
    // ���� ��� ������ ���� ����ϸ�, 5, 4, 3, 2, 1 �� ��µǰ� ���� ���̴�.

    // ������ ������ ���� ��, ���� ������ ���鵵�� �ϰ�ʹٸ� ���� ������ �� �� ����ؾ� �� ���̴�.
    // �̷��� ������ ���ڿ� ���� ������ �ٷ� �� ���� �߻��Ѵ�.
    static void NextPermutation_Incomplete()
    {
        using namespace std;

        std::vector<int> vec{ 5, 4, 3, 2, 1 };

        do
        {
            Print::Container(vec);

        } while (next_permutation(vec.begin(), vec.end()));
    }

    // �κ� �����̳� �����ϱ�
    // ������� �����ڷ� �κ� �����̳ʸ� ������ �� �ִ�.
    static void SubContainer()
    {
        using namespace std;

        // �κ� vector
        vector<int> vec = { 1, 5, 2, 6, 3, 7, 4 };
        int from = 2;
        int to = 5;

        vector<int> subvec(begin(vec) + from, begin(vec) + to + 1);
        Print::Container(subvec);

        // �κ� string
        string str = "abazuzdk";
        string substr(begin(str) + from, begin(str) + to + 1);
        Print::Container(substr);


        // �κ� map
        map<int, string> m = { {1, "aaa"}, {7, "bbb"}, {3, "ccc"}, {2, "dddd"}, {4, "eeeee"}, {5, "fffff"}, {6, "gg"} };
        map<int, string> subm(m.find(3), m.find(5));
        Print::Map(subm);
    }

    // istringstream
    // Ư�� string�� ������� ��ǲ�� ���� ������ ����� �� �ִ�.
    // ������ ���� string�� whitespace�� �����Ͽ� ������ �� �ִ�.
     
    static void Istringstream()
    {
        using namespace std;

        string s = "split\ton   \t white\nspace   .";
        istringstream iss(s);

        string a, b, c, d, e;
        string temp;
        iss >> a >> b >> c >> d >> e;

        vector<string> results = { a, b, c, d, e };
        Print::Container(results);
    }

    // ������ ���� loop�� �̿��� ���� �ִ�.
    static void Istringstream_Loop()
    {
        string s = "split\ton   \t white\nspace   .";
        istringstream iss(s);
        string temp;

        while (iss >> temp)
        {
            cout << temp << endl;
        }
    }
};


