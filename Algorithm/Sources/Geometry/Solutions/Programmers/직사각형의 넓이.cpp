
// 직사각형의 넓이 (Plane Sweeping)
// https://programmers.co.kr/learn/courses/30/lessons/12974

// Plane Sweeping (배열)
// 시간초과

// Plane Sweeping (구간 트리)

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

ll solution(vector<vector<int>> rectangles)
{
    vector<Rectangle> rects(rectangles.size());

    for (int i = 0; i < rectangles.size(); ++i)
    {
        int x1 = rectangles[i][0];
        int y1 = rectangles[i][1];
        int x2 = rectangles[i][2];
        int y2 = rectangles[i][3];

        rects[i] = Rectangle(x1, y1, x2, y2);
    }

    long long answer = UnionArea(rects);

    return answer;
}



int main()
{
    //vector<vector<int> > rectangles = { {0, 1, 4, 4},{3, 1, 5, 3} };
    vector<vector<int> > rectangles = { {1, 1, 6, 5} ,{2, 0, 4, 2},{2, 4, 5, 7},{4, 3, 8, 6},{7, 5, 9, 7} };

    ll answer = solution(rectangles);

    cout << answer;

    return 0;
}



/*
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

using ll = long long;

// 1048576
const int N = 1 << 20;

class LazySegmentTree
{
    LazySegmentTree() :LazySegmentTree(N) {}
    LazySegmentTree(int max_size) : root(1), max_size(max_size)
    {
        tree.assign(max_size * 2, 0);
        lazy.assign(max_size * 2, 0);
    }

    void Add(int add_start, int add_end, int val)
    {
        Add(add_start, add_end, val, root, 1, max_size);
    }

    int Query(int query_start, int query_end)
    {
        return Query(query_start, query_end, root, 1, max_size);
    }

    int Query(int query_start, int query_end, int node, int start, int end)
    {
        //if(query_end < start)
    }

private:
    void Add(int add_start, int add_end, int val, int node, int start, int end)
    {
        int mid = (start + end) / 2;

        // 현재 노드를 유효하게 만든다.
        LazyPropagation(node, start, end);

        // index가 노드가 표현하는 구간과 상관없는 경우 무시
        if (add_end < add_start || add_end < start || end < add_start)
            return;

        // 현재 구간이 완전히 포함되면,
        if (add_start <= start && end <= add_end)
        {
            tree[node] += (end - start + 1) * val;

            // 리프 노드가 아니라면, 요청 저장
            if (start < end)
            {
                lazy[2 * node] += val;
                lazy[2 * node + 1] += val;
            }
            return;
        }

        Add(add_start, add_end, val, 2 * node, start, mid);
        Add(add_start, add_end, val, 2 * node + 1, mid + 1, end);

        // 재귀적으로 Add를 통해 양쪽 자식 노드들도 유효해지기 때문에, Add 이후 현재 구간에 저장해준다.
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    void LazyPropagation(int node, int start, int end)
    {
        // 업데이트 요청이 저장되어 있으면
        if (lazy[node] != 0)
        {
            // 값 갱신
            tree[node] += (end - start + 1) * lazy[node];

            // 리프 노트가 아니라면
            if (start < end)
            {
                // 자식으로 업데이트 요청 전파
                lazy[2 * node] += lazy[node];
                lazy[2 * node + 1] += lazy[node];
            }
            // 현재 노드에 대한 요청을 처리하였으므로 초기화한다.
            lazy[node] = 0;
        }
    }

private:
    int root;
    int max_size;
    vector<ll> tree;
    vector<ll> lazy;
};


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
    // counts[i] = yvec[i] ~ yvec[i + 1] 구간에 겹쳐진 사각형 개수
    //SegmentTree tree(rects.size());

    if (rects.empty()) return 0;

    vector<Event> events;
    map<ll, int> yindexes;

    for (int i = 0; i < rects.size(); ++i)
    {
        const Rectangle& rect = rects[i];
        events.push_back(Event(rect.x1, 1, i));
        events.push_back(Event(rect.x2, -1, i));

        yindexes.insert(make_pair(rect.y1, i));
        yindexes.insert(make_pair(rect.y2, i));
    }

    ll ret = 0;

    sort(begin(events), end(events));

    for (int i = 0; i < events.size(); ++i)
    {
        const Event& ev = events[i];
        const Rectangle& rect = rects[ev.index];

        int from = yindexes[rect.y1];
        int to = yindexes[rect.y2];

        

        //if (i + 1 < events.size())
        //{
        //    ret += cut_length * (events[i + 1].x - ev.x);
        //}
    }

    return ret;
}

ll solution(vector<vector<int>> rectangles)
{
    vector<Rectangle> rects(rectangles.size());

    for (int i = 0; i < rectangles.size(); ++i)
    {
        int x1 = rectangles[i][0];
        int y1 = rectangles[i][1];
        int x2 = rectangles[i][2];
        int y2 = rectangles[i][3];

        rects[i] = Rectangle(x1, y1, x2, y2);
    }

    long long answer = UnionArea(rects);

    return answer;
}



int main()
{
    //vector<vector<int> > rectangles = { {0, 1, 4, 4},{3, 1, 5, 3} };
    vector<vector<int> > rectangles = { {1, 1, 6, 5} ,{2, 0, 4, 2},{2, 4, 5, 7},{4, 3, 8, 6},{7, 5, 9, 7} };

    ll answer = solution(rectangles);

    cout << answer;

    return 0;
}

*/










/*
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

using ll = long long;

// 1048576
const int N = 1 << 20;

class LazySegmentTree
{
public:
    LazySegmentTree() :LazySegmentTree(N) {}
    LazySegmentTree(int size) : root(1), size(size), tree(size * 2), ylens(size * 2), counts(size * 2)
    { }

    void InsertElement(int index, int ylength)
    {
        int leaf_start = size;
        ylens[leaf_start + index] = ylength;
    }
    void ConstructElements()
    {
        for (int i = size - 1; i > 0; i--)
        {
            ylens[i] = ylens[i * 2] + ylens[(i * 2) + 1];
        }
    }


    void Add(int add_start, int add_end)
    {
        Add(add_start, add_end, root, 0, size - 1);
    }

    void Del(int del_start, int del_end)
    {
        Del(del_start, del_end, root, 0, size - 1);
    }

    int Query()
    {
        return tree[root];
    }


private:
    void Add(int add_start, int add_end, int node, int start, int end)
    {
        // index가 노드가 표현하는 구간과 상관없는 경우 무시
        if (add_end < add_start || add_end < start || end < add_start)
            return;

        // 현재 구간이 완전히 포함되면,
        if (add_start <= start && end <= add_end)
        {
            counts[node] ++;
            tree[node] = ylens[node];

            return;
        }

        int mid = (start + end) / 2;
        Add(add_start, add_end, 2 * node, start, mid);
        Add(add_start, add_end, 2 * node + 1, mid + 1, end);

        if(counts[node] == 0)
            tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    void Del(int add_start, int add_end, int node, int start, int end)
    {
        // index가 노드가 표현하는 구간과 상관없는 경우 무시
        if (add_end < add_start || add_end < start || end < add_start)
            return;

        if (add_start <= start && end <= add_end)
        {
            counts[node] --;

            if (counts[node] == 0)
            {
                if (node < size)
                    tree[node] = tree[2 * node] + tree[2 * node + 1];
                else
                    tree[node] = 0;
            }
            return;
        }

        int mid = (start + end) / 2;
        Del(add_start, add_end, 2 * node, start, mid);
        Del(add_start, add_end, 2 * node + 1, mid + 1, end);

        if (counts[node] == 0)
            tree[node] = tree[2 * node] + tree[2 * node + 1];
    }


private:
    int root;
    int size;
    vector<ll> tree;
    vector<ll> ylens;
    vector<ll> counts;
};


struct Rectangle
{
    Rectangle():x1(0), y1(0), x2(0), y2(0){}

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
    // counts[i] = yvec[i] ~ yvec[i + 1] 구간에 겹쳐진 사각형 개수
    if (rects.empty()) return 0;

    vector<Event> events;
    map<ll, int> ymap;

    for (int i = 0; i < rects.size(); ++i)
    {
        const Rectangle& rect = rects[i];
        events.push_back(Event(rect.x1, 1, i));
        events.push_back(Event(rect.x2, -1, i));

        ymap.insert(make_pair(rect.y1, i));
        ymap.insert(make_pair(rect.y2, i));
    }

    LazySegmentTree tree(ymap.size() - 1);

    ll prevy = numeric_limits<ll>::min();
    for (auto e : ymap)
    {
        ll y = e.first;
        int index = e.second;

        if (prevy != numeric_limits<ll>::min())
        {
            tree.InsertElement(index, y - prevy);
        }
        prevy = y;
    }
    tree.ConstructElements();


    ll ret = 0;

    sort(begin(events), end(events));

    for (int i = 0; i < events.size(); ++i)
    {
        const Event& ev = events[i];
        const Rectangle& rect = rects[ev.index];

        int from = ymap[rect.y1];
        int to = ymap[rect.y2] - 1;

        // ev.delta
        if (ev.delta == 1)
            tree.Add(from, to);
        else
            tree.Del(from, to);

        int cut_length = tree.Query();

        if (i + 1 < events.size())
            ret += cut_length * (events[i + 1].x - ev.x);
        

        //if (i + 1 < events.size())
        //{
        //    ret += cut_length * (events[i + 1].x - ev.x);
        //}
    }

    return ret;
}

ll solution(vector<vector<int>> rectangles)
{
    vector<Rectangle> rects(rectangles.size());

    for (int i = 0; i < rectangles.size(); ++i)
    {
        int x1 = rectangles[i][0];
        int y1 = rectangles[i][1];
        int x2 = rectangles[i][2];
        int y2 = rectangles[i][3];

        rects[i] = Rectangle(x1, y1, x2, y2);
    }

    long long answer = UnionArea(rects);

    return answer;
}



int main()
{
    LazySegmentTree tree;


    //vector<vector<int> > rectangles = { {0, 1, 4, 4},{3, 1, 5, 3} };
    vector<vector<int> > rectangles = { {1, 1, 6, 5} ,{2, 0, 4, 2},{2, 4, 5, 7},{4, 3, 8, 6},{7, 5, 9, 7} };

    ll answer = solution(rectangles);

    cout << answer;

    return 0;
}

// 참고
// https://codedoc.tistory.com/421
// https://blog.naver.com/PostView.nhn?blogId=jqkt15&logNo=221981556060

*/