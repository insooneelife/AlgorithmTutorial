
// 기지국 설치 (탐욕법)
// https://programmers.co.kr/learn/courses/30/lessons/12979

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Range
{
    int from, to;
};

bool MergeRange(Range a, Range b, Range& merged)
{
    if (a.to + 1 >= b.from)
    {
        merged = { a.from, b.to };
        return true;
    }

    return false;
}

int solution(int n, vector<int> stations, int w)
{
    vector<Range> ranges;
    vector<Range> merged_ranges;
    ranges.reserve(stations.size());
    merged_ranges.reserve(stations.size());
    for (auto e : stations)
    {
        int from = max(e - w, 1);
        int to = min(e + w, n);
        ranges.push_back({ from, to });
    }

    sort(begin(ranges), end(ranges), [](auto a, auto b) { return a.from < b.from; });
    ranges.push_back({ n + 1, n + 1 });
    merged_ranges.push_back({0, 0});

    for (int i = 0; i < ranges.size(); ++i)
    {
        Range a = merged_ranges.back();
        Range b = ranges[i];
        Range merged;
        if (MergeRange(a, b, merged))
        {
            merged_ranges[merged_ranges.size() - 1] = merged;
        }
        else
        {
            merged_ranges.push_back(b);
        }
    }

    int ans = 0;
    int from = 0;
    int to = 0;
    for (int i = 0; i < merged_ranges.size() - 1; ++i)
    {
        Range a = merged_ranges[i];
        Range b = merged_ranges[i + 1];

        from = a.to + 1;
        to = b.from - 1;

        int k = 2 * w + 1;
        int range = to - from + 1;
        int temp = (range % k > 0) ? 1 : 0;        
        ans += (range / k) + temp;
    }

    return ans;
}

int main()
{
    int n = 16;
    vector<int> stations = { 9 };
    int w = 2;

    cout << solution(n, stations, w);
    
    return 0;
}
