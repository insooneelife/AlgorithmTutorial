
// 화성 지도
// https://www.acmicpc.net/problem/3392

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

using ll = long long;

struct Rectangle
{
    Rectangle() :x1(0), y1(0), x2(0), y2(0) {}

    Rectangle(ll x1, ll y1, ll x2, ll y2)
        : x1(x1), y1(y1), x2(x2), y2(y2)
    {}

    ll x1, y1;
    ll x2, y2;
};

struct Event
{
    Event(ll x, int delta, int index)
        : x(x), delta(delta), index(index)
    {}

    bool operator<(const Event& ev) const
    {
        if (x == ev.x)
        {
            if (delta == ev.delta)
            {
                return index < ev.index;
            }

            return delta < ev.delta;
        }
        return x < ev.x;
    }

    ll x;
    int delta;
    int index;
};

ll UnionArea(const vector<Rectangle>& rects)
{
    if (rects.empty()) return 0;

    vector<Event> events;
    vector<ll> yvec;

    for (int i = 0; i < rects.size(); ++i)
    {
        const Rectangle& rect = rects[i];
        events.push_back(Event(rect.x1, 1, i));
        events.push_back(Event(rect.x2, -1, i));

        yvec.push_back(rect.y1);
        yvec.push_back(rect.y2);
    }

    sort(begin(yvec), end(yvec));
    auto it = unique(begin(yvec), end(yvec));
    yvec.erase(it, end(yvec));

    // counts[i] = yvec[i] ~ yvec[i + 1] 구간에 겹쳐진 사각형 개수
    vector<int> counts(yvec.size() - 1, 0);
    ll ret = 0;

    sort(begin(events), end(events));

    for (int i = 0; i < events.size(); ++i)
    {
        const Event& ev = events[i];
        const Rectangle& rect = rects[ev.index];

        for (int j = 0; j < yvec.size(); ++j)
        {
            ll y = yvec[j];
            if (rect.y1 <= y && y < rect.y2)
            {
                counts[j] += ev.delta;
            }
        }

        ll cut_length = 0;
        for (int j = 0; j < yvec.size() - 1; ++j)
        {
            if (counts[j] > 0)
            {
                cut_length += yvec[j + 1] - yvec[j];
            }
        }

        if (i + 1 < events.size())
        {
            ret += cut_length * (events[i + 1].x - ev.x);
        }
    }

    return ret;
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n;

    vector<Rectangle> rects(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> rects[i].x1 >> rects[i].y1 >> rects[i].x2 >> rects[i].y2;
    }

    cout << UnionArea(rects) << endl;

    return 0;
}
