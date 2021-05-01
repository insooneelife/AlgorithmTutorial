#pragma once


#include "Headers.h"
#include "Utility.h"

class STL
{
public:

    // sort
    // 정렬된 컨테이너를 반환한다.
    static void Sort()
    {
        using namespace std;

        vector<int> numbers = { 3, 2, 1, 5, 4 };
        sort(begin(numbers), end(numbers));

        Print::Container(numbers);
    }

    // find
    // 특정 원소를 찾고, 그 원소의 반복자를 반환한다.
    static void Find()
    {
        using namespace std;

        vector<int> numbers = { 3, 2, 1, 5, 4 };
        auto it = find(begin(numbers), end(numbers), 3);

        cout << *it << endl;
    }

    // erase
    // 반복자를 인자로 받아 그 반복자 위치의 원소를 제거한다.
    // find와 같이 사용하면 특정 원소를 제거할 수 있다.
    static void Erase()
    {
        using namespace std;

        vector<int> numbers = { 1, 3, 2, 3, 1, 5, 4, 5 };
        auto it = find(begin(numbers), end(numbers), 3);
        numbers.erase(it);

        Print::Container(numbers);
    }

    // erase range
    // 반복자 두개를 인자로 받아 그 반복자들 사이의 모든 원소를 제거한다.
    static void EraseRange()
    {
        using namespace std;

        vector<int> numbers = { 1, 3, 2, 3, 1, 5, 4, 5 };
        numbers.erase(begin(numbers) + 1, begin(numbers) + 4);

        Print::Container(numbers);
    }


    // unique
    // 중복된 원소들을 모두 뒤로 보내고, 중복원소들의 시작 반복자를 반환한다.
    // 컨테이너가 정렬된 상태여야 정상동작한다.
    // 중복원소를 컨테이너에서 모두 제거하려면 범위에 대한 erase와 같이 사용하면 된다.
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
    // 컨테이너 내의 최대 원소와, 최소 원소의 반복자를 반환한다.
    static void MinMaxElement()
    {
        using namespace std;

        vector<int> v = { 1, 2, 3, 4, 5 };
        int max_val = *max_element(begin(v), end(v));
        int min_val = *min_element(begin(v), end(v));
        cout << max_val << " " << min_val;
    }

    // set_difference
    // 컨테이너에서 다른 컨테이너의 모든 원소를 제거한 새로운 컨테이너를 반환한다.
    // 일반 컨테이너의 경우 원소가 정렬된 상태여야 한다.
    static void SetDifference()
    {
        using namespace std;

        vector<int> v = { 1, 2, 3, 4, 5 };
        vector<int> u = { 1, 3, 5 };
        vector<int> output;
        set_difference(begin(v), end(v), begin(u), end(u), std::back_inserter(output));

        Print::Container(v);
    }

    // 컨테이너의 종류가 다르더라도 가능하다.
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
    // 한 컨테이너가 다른 컨테이너의 부분집합인지 확인한다.
    // 컨테이너가 정렬된 상태여야 정상동작한다.
    // 부분집합 확인함수
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
    // 컨테이너의 다음 순열을 반환한다.
    // 다음과 같은 방법으로 모든 순열을 출력할 수 있다.
    static void NextPermutation()
    {
        using namespace std;

        std::vector<int> vec{ 1, 2, 3, 4, 5 };

        do
        {
            Print::Container(vec);

        } while (next_permutation(vec.begin(), vec.end()));
    }

    // 주의할 점은, 현재 상태를 기준으로 다음 순열을 반환하기 때문에,
    // 모든 순열을 순회하기를 기대하며 사용한다면 인풋에 정렬 상태를 확인해야한다.
    // 예를 들어 다음과 같이 사용하면, 5, 4, 3, 2, 1 만 출력되고 끝날 것이다.

    // 원소의 종류가 같을 때, 같은 순열을 만들도록 하고싶다면 먼저 정렬을 한 후 사용해야 할 것이다.
    // 이러한 문제는 문자열 순열 문제를 다룰 때 자주 발생한다.
    static void NextPermutation_Incomplete()
    {
        using namespace std;

        std::vector<int> vec{ 5, 4, 3, 2, 1 };

        do
        {
            Print::Container(vec);

        } while (next_permutation(vec.begin(), vec.end()));
    }

    // 부분 컨테이너 생성하기
    // 범위기반 생성자로 부분 컨테이너를 생성할 수 있다.
    static void SubContainer()
    {
        using namespace std;

        // 부분 vector
        vector<int> vec = { 1, 5, 2, 6, 3, 7, 4 };
        int from = 2;
        int to = 5;

        vector<int> subvec(begin(vec) + from, begin(vec) + to + 1);
        Print::Container(subvec);

        // 부분 string
        string str = "abazuzdk";
        string substr(begin(str) + from, begin(str) + to + 1);
        Print::Container(substr);


        // 부분 map
        map<int, string> m = { {1, "aaa"}, {7, "bbb"}, {3, "ccc"}, {2, "dddd"}, {4, "eeeee"}, {5, "fffff"}, {6, "gg"} };
        map<int, string> subm(m.find(3), m.find(5));
        Print::Map(subm);
    }

    // istringstream
    // 특정 string을 대상으로 인풋과 같은 연산을 사용할 수 있다.
    // 다음과 같이 string의 whitespace를 제거하여 저장할 수 있다.
     
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

    // 다음과 같이 loop로 이용할 수도 있다.
    static void Istringstream_Loop()
    {
        using namespace std;

        string s = "split\ton   \t white\nspace   .";
        istringstream iss(s);
        string temp;

        while (iss >> temp)
        {
            cout << temp << endl;
        }
    }
};


