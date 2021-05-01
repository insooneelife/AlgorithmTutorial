// C++ STL 해시 테이블 (unordered_map)

// 기본 사용



#include <unordered_map>
#include <iostream>
#include <string>

using namespace std;

struct Point
{
public:
    Point() : x(0), y(0) {}
    Point(int x, int y) : x(x), y(y) {}

public:
    int x, y;
};

// x, y의 범위가 10000 미만인 경우
int ToKey(Point p)
{
    return p.x * 10000 + p.y;
}

int main()
{
    // 기본 이용방법은 다음과 같다.
    unordered_map<int, string> umap;
    umap.insert(make_pair(1, "mom"));
    umap.insert(make_pair(2, "dad"));
    umap.insert(make_pair(3, "baby"));







    // 어떤 좌표 (x, y) 가 인풋으로 들어오는 경우도 해시테이블을 이용하여 저장할 수 있을 것이다.
    unordered_map<int, Point> points;
    points.insert(make_pair(1, Point(4, 7)));
    points.insert(make_pair(2, Point(2, 5)));
    points.insert(make_pair(3, Point(0, 2)));

    for (auto e : umap)
    {
        cout << e.first << " " << e.second << endl;
    }

    // 하지만 이 경우, key 값을 사용자가 임의로 지정해 주어야 할까?
    // 굉장히 다양한 좌표 데이터들이 저장될 수 있을텐데, 그것들의 key를 일일이 사용자가 지정해주는것은 너무 어려운 일이고,
    // 또한 어떤 좌표 (x, y)를 해시테이블에서 찾고 싶을때 key -> (x, y)로는 맵을 통해 참조가 가능하지만, (x, y) -> key로는 불가능하다.
    // 그러므로 value에서 일관된 고유식별자(key)를 생성하는 규칙을 정의하면 좋을 것이다.

    Point p1 = Point(12, 52);
    points.insert(make_pair(ToKey(p1), p1));

    Point p2 = Point(2, 32);
    points.insert(make_pair(ToKey(p2), p2));

    // 이렇게 사용한다면, key -> value, value -> key 모두 자유롭게 사용할 수 있게 된다.
    // 하지만, 지금 이 방법은 굉장히 제한적인 상황에서만 사용이 가능하다.
    // x, y의 범위가 10000이하로 정해져있기도 하고,
    // 지금보다 더 복잡한 복합 데이터에 대해서는 int type으로 커버할 수 없는 key 조합수가 나올수도 있기 때문이다.   


    return 0;
}