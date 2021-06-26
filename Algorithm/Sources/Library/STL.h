#pragma once


#include "Headers.h"
#include "Utility.h"

class STL
{
public:

    // cin, cout의 입출력 속도를 증가시켜준다. (백준에서 입출력 속도로 통과되지 않는 경우 해결)
    // 주의
    // 1. scanf, printf와 함께 사용하면 문제가 생길 수 있다.
    // 2. 싱글 쓰레드 환경에서만 사용 가능하다.

    static void InputOutputSpeed()
    {
        using namespace std;
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);
        cout.tie(NULL);
    }

    // reserve
    // 컨테이너의 capacity를 바꾸어준다.
    static void Reserve()
    {
        using namespace std;

        vector<int> candidates;
        candidates.reserve(100);

        for (int i = 0; i < 50; ++i)
        {
            candidates.push_back(i);
        }

        cout << candidates.size();
    }

    // sort
    // 정렬된 컨테이너를 반환한다.
    static void Sort()
    {
        using namespace std;

        vector<int> numbers = { 3, 2, 1, 5, 4 };
        sort(begin(numbers), end(numbers));

        Print::Container(numbers);
    }

    // 문자열 정렬
    // 사전식 오름차순, 사전식 내림차순, 사전식 비교
    static void StringSort()
    {
        using namespace std;
        vector<string> v = { "zaa", "abc", "bac" "classicc", "pop", "classic", "pop", "pop", "classicc", "sga" };

        // 기본, 사전식 오름차순
        sort(begin(v), end(v));
        Print::Container(v, "--------------sorted1-------------");

        // 람다, 사전식 내림차순
        sort(begin(v), end(v), [](const string& a, const string& b) { return a > b; });
        Print::Container(v, "--------------sorted2-------------");

        // 람다, 사전식 내림차순 내림차순 (직접)
        sort(begin(v), end(v), [](const string& a, const string& b)
            {
                return lexicographical_compare(begin(a), end(a), begin(b), end(b), [](char a, char b)
                    {
                        return a > b;
                    });
            });
        Print::Container(v, "--------------sorted3-------------");
    }

    // find
    // 특정 원소를 찾고, 그 원소의 반복자를 반환한다.
    static void Find()
    {
        using namespace std;

        vector<int> numbers = { 3, 2, 1, 5, 4 };
        auto it = find(begin(numbers), end(numbers), 3);
        int index = it - numbers.begin();

        if (it != end(numbers))
        {
            cout << *it << " " << index << endl;
        }
        else
        {
            // (index == numbers.size) in here
            cout << index << endl;
        }
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
    // 컨테이너가 비어있는 경우 segment error
    static void MinMaxElement()
    {
        using namespace std;

        vector<int> v = { 1, 2, 3, 4, 5 };
        int max_val = *max_element(begin(v), end(v));
        int min_val = *min_element(begin(v), end(v));
        cout << max_val << " " << min_val;

        // lambda
        vector<int> data = { 1, 2, 3, 7, -10, 5 };
        int min = *min_element(begin(data), end(data), [](int a, int b) { return a < b; });
        cout << min;
    }

    // count, count_if
    // 컨테이너 내에서 특정 원소를 카운팅한다.
    static void CountElement()
    {
        using namespace std;

        vector<int> v = { 10, 20, 30, 30, 20, 10, 10, 20 };

        int cnt1 = std::count(begin(v), end(v), 20);
        int cnt2 = std::count_if(begin(v), end(v), [](int e) { return e <= 20; });

        cout << cnt1 << " " << cnt2;
    }

    // fill
    // 컨테이너에서 원소를 다른 값으로 수정한다.
    // 마찬가지로 vector와 같은 다른 컨테이너에서도 사용 가능하다.
    static void FillElement()
    {
        using namespace std;

        string str = "01033334444";
        fill(begin(str), end(str) - 4, '*');

        // ******4444
        cout << str;
    }

    // set_intersection
    // 두 컨테이너에 교집합을 구한다.
    // 일반 컨테이너의 경우 원소가 정렬된 상태여야 한다.
    static void SetIntersection()
    {
        using namespace std;

        vector<int> v = { 1, 2, 3, 4, 5 };
        vector<int> u = { 1, 3, 5 };
        vector<int> output;

        sort(begin(v), end(v));
        sort(begin(u), end(u));
        set_intersection(begin(v), end(v), begin(u), end(u), std::back_inserter(output));

        Print::Container(output);
    }

    // set_union
    // 두 컨테이너의 합집합을 구한다.
    // 일반 컨테이너의 경우 원소가 정렬된 상태여야 한다.
    static void SetUnion()
    {
        using namespace std;
        vector<int> a = { 1, 2, 3 };
        vector<int> b = { 1, 2, 4, 5 };
        vector<int> c;

        sort(begin(a), end(a));
        sort(begin(b), end(b));
        std::set_union(begin(a), end(a), begin(b), end(b), back_inserter(c));

        Print::Container(c);
    }

    // set_union
    // 중복이 있는 경우도 합집합을 구할 수 있다.
    // 일반 컨테이너의 경우 원소가 정렬된 상태여야 한다.
    static void SetUnionWithOverlap()
    {
        using namespace std;

        vector<int> a = { 1, 1, 2, 2, 3 };
        vector<int> b = { 1, 2, 2, 4, 5 };
        vector<int> c;

        sort(begin(a), end(a));
        sort(begin(b), end(b));
        std::set_union(begin(a), end(a), begin(b), end(b), back_inserter(c));

        Print::Container(c);
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

        sort(begin(v), end(v));
        sort(begin(u), end(u));
        set_difference(begin(v), end(v), begin(u), end(u), std::back_inserter(output));

        Print::Container(output);
    }

    // 컨테이너의 종류가 다르더라도 가능하다.
    static void SetDifference_VectorToSet()
    {
        using namespace std;

        vector<int> v = { 1, 2, 3, 4, 5 };
        set<int> u = { 1, 3, 5 };
        vector<int> output;

        sort(begin(v), end(v));
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
        sort(begin(vec), end(vec));

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
        // sort(begin(vec), end(vec));
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

    // set은 return의 두번째 값을 통해 중복여부를 확인할 수 있다.
    static void Set_Return()
    {
        using namespace std;
        set<int> s = { 1, 2, 3 };

        pair<set<int>::iterator, int> pair = s.insert(4);
        cout << pair.second << endl;

        pair = s.insert(4);
        cout << pair.second << endl;
    }

    // string에서 문자열을 찾는 예제(html에서 body부분만 잘라오기)
    static void StringFindBody()
    {
        using namespace std;
        const string page = "<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://a.com\"/>\n</head>  \n<body>\nBlind Lorem Blind ipsum dolor Blind test sit amet, consectetur adipiscing elit. \n<a href=\"https://b.com\"> Link to b </a>\n</body>\n</html>";

        static const string kStartBody = "<body>";
        static const string kEndBody = "</body>";
        int start_idx = page.find(kStartBody) + kStartBody.size();
        int end_idx = page.find(kEndBody, start_idx);
        int size = end_idx - start_idx;

        string body = page.substr(start_idx, size);
        cout << body;
    }

    // string을 특정 character로 특정 개수만큼 채우며 초기화한다.
    static void StringInit()
    {
        using namespace std;
        string A(15, 'A');
        string B(1, 'B');
        cout << A;
    }

    // string을 int로 변환하는 예제이다.
    static void StringToInt()
    {
        using namespace std;
        string valid = "12333aaa";
        string not_valid = "a12333abb";

        // print 12333
        cout << stoi(valid) << endl;

        // error
        //cout << stoi(not_valid) << endl;
    }

    // 숫자를 표현하는데에 공간을 할당해주고, 할당공간에서 여분공간이 생기면 특정 문자로 출력해준다.
    // 숫자가 할당공간을 넘어가면 그냥 숫자값으로 출력된다.
    // ex)
    // 할당공간 : 5, 문자 : '0'
    // 25 -> 00025
    // 255555 -> 255555
    static void SetFill()
    {
        using namespace std;

        cout << setfill('0') << setw(6) << 333 << endl;

        cout << setfill('f') << setw(6) << 333 << endl;

        cout << setfill('0') << setw(6) << "333" << endl;

        cout << setfill('0') << setw(6) << 3333333 << endl;

        
        // stringstream 으로 이용하면 직접 문자열로 가져올 수 있다.
        // stringstream 을 이용하는 경우 endl을 조심하자
        stringstream ss;
        ss << setfill('0') << setw(5) << 255;
        string str = ss.str();
        cout << str << endl;
    }
    
    // transform
    // 컨테이너의 원소들을 순회하며 바꾸는 함수이다.
    static void Transform()
    {
        using namespace std;
        vector<int> vec = { 1, 2, 3, 4, 5 };
        Print::Container(vec);

        // vec 컨테이너의 [begin, end) 범위의 값에 2를 곱한 값을 begin부터 저장한다.
        transform(begin(vec), end(vec), begin(vec), [](int e) { return e * 2; });
        Print::Container(vec);

        // 다른 컨테이너로 출력도 가능하다.
        vector<int> out(vec.size());
        transform(begin(vec), end(vec), begin(out), [](int e) { return e * 2; });
        Print::Container(out);
    }

    // set을 이중 우선순위큐로 사용하는 예제이다.
    static void MinMaxElementInSet()
    {
        using namespace std;
        set<int> S = { 1, 5, 7, 3, 15, 2 };

        auto it = S.begin();
        auto rit = S.end();
        --rit;

        cout << *it << " " << *rit << endl;

        S.erase(it);
        S.erase(rit);

        for (auto e : S)
        {
            cout << e << endl;
        }
    }

    // splice
    // 연결리스트를 다른 연결리스트에 붙이는 예제와,
    // 연결리스트의 일부분을 떼서 다른 위치에 붙이는 예제이다.
    static void SpliceList()
    {
        using namespace std;
        // example 1.
        {
            list<int> l = { 1, 2, 3, 4, 5, 6, 7 };
            list<int> m = { 1, 2, 3 };

            l.splice(l.end(), m, begin(m), end(m));

            Print::Container(l);
        }

        // example 2.
        { 
            list<int> l = { 1, 2, 3, 4, 5, 6, 7 };

            auto it = begin(l);
            it++; 
            it++;

            l.splice(l.end(), l, begin(l), it);
            Print::Container(l);
        }
    }

    // partial_sum
    // 부분합을 만드는 예제이다.
    static void PartialSum()
    {
        using namespace std;

        vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        vector<int> sum(v.size());
        vector<int> mul(v.size());

        partial_sum(begin(v), end(v), begin(sum));
        //partial_sum(begin(v), end(v), begin(sum), plus<int>());
        partial_sum(begin(v), end(v), begin(mul), multiplies<int>());

        Print::Container(sum);
        Print::Container(mul);
    }

    // chrono 
    // 시간측정을 위한 예제이다.
    void TimeCalculation()
    {
        using namespace std;
        auto from = chrono::system_clock::now();
        auto from_ms = chrono::time_point_cast<chrono::milliseconds>(from);

        cout << "job here" << endl;

        auto to = chrono::system_clock::now();
        auto to_ms = chrono::time_point_cast<chrono::milliseconds>(to);
        long duration = (to_ms.time_since_epoch() - from_ms.time_since_epoch()).count();

        cout << duration << " ms" << endl;
    }
};


