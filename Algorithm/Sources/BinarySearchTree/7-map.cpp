// STL Binary Search Tree
// C++ STL에는 이미 잘 만들어진 이진탐색트리가 존재한다. (레드블랙트리)

#include <iostream>
#include <map>
#include "Print.h"
using namespace std;

int main()
{
    // 키 값을 기준으로 원소가 정렬됨
    map<int, string> tree = { {1, "blbl"}, {5, "ffsf"}, {3, "kgkgk"} , {13, "bba"} , {7, "dddd"} , {8, "eeee"} };

    Print::Map(tree, "default");

    // 탐색
    auto it = tree.find(5);
    if (it != end(tree))
    {
        cout << "search : " << it->first << " " << it->second << endl << endl;
    }

    // 삽입
    tree.insert(make_pair(8, "ffds"));
    tree[-55] = "kgkg";

    Print::Map(tree, "insert");

    // 삭제
    tree.erase(1);
    Print::Map(tree, "delete");
    

    // 이진탐색트리는 내부적으로 정렬된 상태로 데이터를 관리하기 때문에,
    // 범위 기반 질의(Range Based Query)에 강하다.
    // STL map에서도 범위기반 질의를 편하게 사용하도록 하기 위해, lower_bound와 upper_bound를 지원한다.
    // 이 연산자는 find와 달리 특정 원소를 타겟으로 반복자 위치를 찾는것이 아니라,
    // 경계값으로 키 값을 넣어서 트리 내부에서 그 값의 경계가 되는 반복자 위치를 가져오도록 한다. (경계는 위를 기준으로 or 아래를 기준으로 가능하다.)
    // upper_bound와 lower_bound로 두 개의 경계가 되는 반복자 위치를 가져왔다면,
    // 이 위치를 기반으로 for 루프를 돌며 그 범위 내의 모든 값을 순회할 수 있다.

    auto lower = tree.lower_bound(3);
    auto upper = tree.upper_bound(7);

    for (auto it = lower; it != upper; ++it)
    {
        cout << it->first << " " << it->second << endl;
    }

    return 0;
}