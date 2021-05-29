// 쿼드압축 후 개수 세기
// https://programmers.co.kr/learn/courses/30/lessons/68936

#include <vector>
#include <iostream>
using namespace std;

struct Idx
{
    int i, j;
};

const vector<int> zero = { 1, 0 };
const vector<int> one = { 0, 1 };

bool CheckAll(const vector<vector<int>>& all, const vector<int>& target)
{
    for (const auto& e : all)
        if (e != target)
            return false;
    return true;
}

vector<int> AddVec(const vector<int>& a, const vector<int>& b)
{
    vector<int> c(a.size(), 0);
    for (int i = 0; i < a.size(); ++i)
    {
        c[i] = a[i] + b[i];
    }
    return c;
}

// 전체 구간에 대한 arr를 압축 후 (0, 1) 개수 반환
vector<int> Quadtree(const vector<vector<int>>& arr, Idx from, Idx to)
{
    if (from.i == to.i)
        return arr[from.i][from.j] == 0 ? zero : one;

    const int N = (to.i - from.i) + 1;
    Idx mid = { from.i + N / 2 - 1, from.j + N / 2 - 1 };

    vector<pair<Idx, Idx>> ranges =
    {
        { from, mid },
        {{ from.i, mid.j + 1 }, { mid.i, to.j }},
        {{ mid.i + 1, from.j }, { to.i, mid.j }},
        {{ mid.i + 1, mid.j + 1 }, to}
    };

    // 각 구간에 대한 (0, 1) 개수
    vector<vector<int>> all(ranges.size(), vector<int>(2, 0));
    vector<int> sum(2, 0);

    for (int i = 0; i < ranges.size(); ++i)
    {
        const auto& e = ranges[i];
        all[i] = Quadtree(arr, e.first, e.second);
        sum = AddVec(sum, all[i]);
    }

    if (CheckAll(all, one))
        return one;

    if (CheckAll(all, zero))
        return zero;

    return sum;
}

vector<int> solution(vector<vector<int>> arr)
{
    const int N = arr.size();
    return Quadtree(arr, { 0, 0 }, { N - 1, N - 1 });
}


int main()
{
    /*
    vector<vector<int>> arr = 
    {
        {1, 1, 0, 0},
        {1, 0, 0, 0},
        {1, 0, 0, 1},
        {1, 1, 1, 1} 
    };
    */

    vector<vector<int>> arr =
    {
        {1, 1, 1, 1, 1, 1, 1, 1},
        {0, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 1, 1, 1, 1},
        {0, 1, 0, 0, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 1, 0, 0, 1},
        {0, 0, 0, 0, 1, 1, 1, 1}
    };

    auto answer = solution(arr);
    cout << answer[0] << " " << answer[1] << endl;

    return 0;
}

