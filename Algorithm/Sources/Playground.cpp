// C++ STL 해시 테이블 (unordered_map)

// 기본 사용



#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <string>

using namespace std;

struct Point
{
public:
    Point() : x(0), y(0) {}
    Point(int x, int y) : x(x), y(y) {}

    // 이 데이터가 key로서 사용되도록 하기 위해서는 고유식별기능이 필요하다.
    // operator== 을 통해 Equal 비교가 가능하도록 하여 고유식별이 가능하도록 한다.
    bool operator==(const Point& other) const
    {
        return x == other.x && y == other.y;
    };

public:
    int x, y;
};


struct KeyHasher
{
    // 해시 함수 정의
    // Bucket에 저장될 위치를 해싱하기 위해 x값과 y값이 골고루 사용되도록 한다.
    std::size_t operator()(const Point& k) const
    {
        size_t res = 17;
        res = res * 31 + hash<int>()(k.x);
        res = res * 31 + hash<int>()(k.y);            
        return res;
    }
};

int main()
{
    // 이 문제를 해결하기 위해 value를 그 자체로 key 처럼 사용해버리는 방법이 있다. 
    unordered_set<Point, KeyHasher> points;

    points.insert(Point(5, 4));
    points.insert(Point(25, 14));
    points.insert(Point(57, 41));
    points.insert(Point(53, 14));
    points.insert(Point(53, 17));
    points.insert(Point(57, 14));

    // operator==을 통해 같은 데이터가 이미 있다면 무시된다.
    points.insert(Point(53, 14));

    for (auto e : points)
    {
        cout << e.x << " " << e.y << endl;
    }
    cout << endl;


    // 물론 unordered_map에서도 이와 같은 방법으로 사용이 가능하다.
    // (하지만 현재로서는 value 부분에 딱히 넣어줄 데이터가 없다.)

    unordered_map<Point, int, KeyHasher> points_map;

    points_map.insert(make_pair(Point(5, 4), 0));
    points_map.insert(make_pair(Point(25, 14), 0));
    points_map.insert(make_pair(Point(57, 41), 0));

    for (auto e : points_map)
    {
        cout << e.first.x << " " << e.first.y << endl;
    }

    return 0;
}