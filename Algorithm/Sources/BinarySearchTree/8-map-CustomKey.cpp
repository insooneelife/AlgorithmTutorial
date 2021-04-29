#include <iostream>
#include <map>
#include <set>
#include <string>
#include "Print.h"
using namespace std;

// 위치를 키로 하고 이름 값으로 저장하는 map을 생각해보자.
// 하지만 tree에서 데이터에 대해 탐색, 삽입, 삭제 등 모든 연산을 수행하기 위해서 키에 대한 비교가 가능해야한다.
// 그러므로 Point 구조체에는 비교 연산자를 정의해줄 필요가 있다.


struct Point
{
    Point() :x(0), y(0) {}
    Point(int x, int y) : x(x), y(y) {}


    // for less
    bool operator<(const Point& other) const
    {
        if (x == other.x)
            return y < other.y;

        return x < other.x;
    }

    // for greater
    bool operator>(const Point& other) const
    {
        if (x == other.x)
            return y > other.y;

        return x > other.x;
    }


public:
    int x;
    int y;
};

int main()
{
    map<Point, string> tree = { {Point(5, 7), "june"}, {Point(5, 7), "tom"}, {Point(5, 7), "jack"}, {Point(5, 7), "mina"} };

    for (auto e : tree)
    {
        cout << e.first.x << " " << e.first.y << " " << e.second << endl;
    }
    cout << endl;


    // 같은 방법으로 set도 이용 가능하다.
    // set은 unordered_set과 같은 인터페이스를 이용하며,
    // 값은 따로 저장하지 않고 키만 저장하는 형태의 이진탐색트리이다.

    set<Point> tree2 = { Point(5, 7), Point(5, 8), Point(6, 6), Point(6, 7),Point(6, 8), };

    for (Point p : tree2)
    {
        cout << p.x << " " << p.y << endl;
    }
    cout << endl;


    // 또한 map, set 모두 키에 대해 오름차순으로 트리를 유지할 수도 있겠지만,
    // 내림차순으로 트리를 유지해야하는 상황도 생길 수 있을 것이다.
    // 그런 상황을 위해 map과 set은 트리 내부 비교 연산 정책을 수정할 수 있도록 설계되어있다.
    // 하지만 내림차순으로 트리를 구성하려면 operator>를 추가로 정의해주어야 한다.
    set<Point, greater<Point>> tree3 = { Point(5, 7), Point(5, 8), Point(6, 6), Point(6, 7),Point(6, 8), };

    for (Point p : tree3)
    {
        cout << p.x << " " << p.y << endl;
    }
    cout << endl;

    return 0;
}