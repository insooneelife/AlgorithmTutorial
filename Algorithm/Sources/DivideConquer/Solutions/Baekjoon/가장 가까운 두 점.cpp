
// 가장 가까운 두 점 (분할정복)
// https://www.acmicpc.net/problem/2261

// 시행착오
// 1. float으로 인한 오차 문제
// 2. 기저 조건 원소가 하나일 때 infinite을 리턴하는것은 위험함 -> 원소가 둘인경우와, 셋인 경우로 기저를 수정
// 3. 실수로 candidate을 활용하지 않고 points를 이용함
// 4. 동일한 점이 인풋으로 들어오는 경우
// 5. 모든 점들의 x값이 동일한 경우

// 문제 풀이

// Closest(from, to)
// [from, to] 범위의 가장 가까운 두 점의 거리제곱을 반환하는 함수
// Closest(from, mid), Closest(mid + 1, to)가 각각 왼쪽 집합에서 최소거리와, 오룬쪽 집합에서의 최소거리를 반환한다고 가정한다.
// 왼쪽집합과 오른쪽집합에 걸쳐 있는 두 점을 선택하는 경우에 대해 해결한다.
// (왼쪽집합의 최대 x + 오른쪽집합의 최소 x) / 2 로 수직선 x를 만들고, 
// (왼쪽집합 최소거리, 오른쪽집합 최소거리)을 통해 최소거리 mindis를 구한다.
// 수직선 x를 기준으로 [from, to] 범위의 점들 중, abs(p.x - x)가 mindis보다 작은 점들만 선별한다. 
// (각 점은 수직선 건너편의 점과 매칭되어야 하는데, 수직선까지의 거리부터 mindis보다 커버리면 이미 그 점은 검사할 필요가 없다.)
// 선별된 점들을 y값 기준으로 정렬한다.
// 정렬된 점들 중 서로 다른 두 점을 선택하는데, 두 점의 y값 차이가 mindis를 넘지 않도록 선택한다.
// 정렬이 되어있기 때문에 2중 루프를 통해 선택하되, y값 차이가 mindis를 넘어가는 경우 break를 하면 시간초과를 피할 수 있다.

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

struct Point
{
    int x, y;

    bool operator<(const Point& other) const
    {
        return x < other.x;
    }
};

int Distance(const Point& a, const Point& b)
{
    return (b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y);
}

int Closest(const vector<Point>& points, int from, int to)
{
    if (from + 1 == to)
        return Distance(points[from], points[to]);

    if (from + 2 == to)
    {
        int d1 = Distance(points[from], points[from + 1]);
        int d2 = Distance(points[from + 1], points[from + 2]);
        int d3 = Distance(points[from + 2], points[from]);

        return min(d1, min(d2, d3));
    }    

    int mid = (from + to) / 2;
    int ldis = Closest(points, from, mid);
    int rdis = Closest(points, mid + 1, to);

    int mindis = min(ldis, rdis);
    int x = (points[mid].x + points[mid + 1].x) / 2;
    
    vector<Point> candidates;
    candidates.reserve(to - from + 1);

    for (int i = from; i <= to; ++i)
    {
        int diff = points[i].x - x;
        if (diff * diff < mindis)
        {
            candidates.push_back(points[i]);
        }
    }
    
    if (candidates.empty()) 
        return mindis;

    sort(begin(candidates), end(candidates), [](const Point& a, const Point& b) { return a.y < b.y; });

    for (int i = 0; i < candidates.size() - 1; ++i)
    {
        Point lpoint = candidates[i];
        for (int j = i + 1; j < candidates.size(); ++j)
        {
            Point rpoint = candidates[j];
            int diff = (lpoint.y - rpoint.y);

            if (diff * diff >= mindis)
                break;

            mindis = min(mindis, Distance(lpoint, rpoint));
        }
    }

    return mindis;
}

int main()
{
    int n;
    int x, y;
    vector<Point> points;
    cin >> n;

    for (int i = 0; i < n; ++i)
    {
        cin >> x >> y;
        points.push_back({ x, y });
    }

    sort(begin(points), end(points));
    cout << Closest(points, 0, points.size() - 1) << endl;

    return 0;
}
