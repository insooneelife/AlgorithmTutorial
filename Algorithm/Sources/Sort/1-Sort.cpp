#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

void Print(const vector<int>& v, string tag = "----------------------------")
{
    cout << tag << endl;
    for (auto e : v)
    {
        cout << e << " ";
    }
    cout << endl;
}

int main()
{
    vector<int> plays{ 3, 500, 2, 600, 5, 150, 800, 1, 2500, 800 };

    Print(plays, "--------------default-------------");

    // 기본, 오름차순
    sort(begin(plays), end(plays));

    // 람다, 내림차순
    //sort(begin(plays), end(plays), [](int a, int b) { return a > b; });

    // 기본, 반쪽만 정렬
    //sort(begin(plays) + plays.size() / 2, end(plays));
    //sort(begin(plays), begin(plays) + plays.size() / 2);

    // 람다, 값이 threshold 보다 크면 -> 내림차순, 작거나 같으면 오름차순, 큰 애들이 뒤로
    /*
    int threshold = 550;
    sort(begin(plays), end(plays), [threshold](int a, int b)
    {
        if (a > threshold && b > threshold)
        {
            return a > b;
        }
        else
        {
            return a < b;
        }
    });
    */

    Print(plays, "--------------sorted-------------");

    return 0;
}