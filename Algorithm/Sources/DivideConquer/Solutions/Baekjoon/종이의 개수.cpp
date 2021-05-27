
// 종이의 개수
// https://www.acmicpc.net/problem/1780

#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

struct Idx
{
    int i, j;
};

std::vector<int> AddVec(const std::vector<int>& a, const std::vector<int>& b)
{
    using namespace std;
    std::vector<int> c(a.size());
    for (int i = 0; i < a.size(); ++i)
    {
        c[i] = a[i] + b[i];
    }
    return c;
}

const vector<int> mone = { 1, 0, 0 };
const vector<int> zero = { 0, 1, 0 };
const vector<int> one = { 0, 0, 1 };
const vector<int> allmone = { 9, 0, 0 };
const vector<int> allzero = { 0, 9, 0 };
const vector<int> allone = { 0, 0, 9 };

// fa     |        |
//     ta |        |
//---------------------------
//        | fb     |
//        |     tb |
//---------------------------
//        |        | fc
//        |        |     tc
//
static vector<int> NonaDivision(std::vector<std::vector<int>>& board, Idx from, Idx to)
{
    using namespace std;
    // length 
    const int N = (to.i - from.i) + 1;
    if (N == 1)
    {
        int val = board[from.i][from.j];
        if (val == 0)
            return zero;
        else if (val == 1)
            return one;
        else
            return mone;
    }

    Idx fa = from;
    Idx ta = { from.i + N / 3 - 1, from.j + N / 3 - 1 };
    Idx fb = { ta.i + 1, ta.j + 1 };
    Idx tb = { from.i + 2 * N / 3 - 1, from.j + 2 * N / 3 - 1 };
    Idx fc = { tb.i + 1, tb.j + 1 };
    Idx tc = to;

    vector<pair<Idx, Idx>> from_to =
    {
        {fa, ta},                       // left, top
        {{fa.i, fb.j}, {ta.i, tb.j}},   // mid, top
        {{fa.i, fc.j}, {ta.i, tc.j}},   // right, top 

        {{fb.i, fa.j}, {tb.i, ta.j}},   // left, mid
        {fb, tb},                       // mid, mid
        {{fb.i, fc.j}, {tb.i, tc.j}},   // right, mid

        {{fc.i, fa.j}, {tc.i, ta.j}},   // left, mid
        {{fc.i, fb.j}, {tc.i, tb.j}},   // right, mid
        {fc, tc},                       // mid, mid
    };

    vector<int> now = { 0, 0, 0 };
    for (int i =0; i < from_to.size(); ++i)
    {
        const auto& e = from_to[i];
        now = AddVec(now, NonaDivision(board, e.first, e.second));
    }

    if (now == allzero)
        return zero;
    else if (now == allone)
        return one;
    else if (now == allmone)
        return mone;
    else
        return now;
    
}


int main()
{
    int n;
    cin >> n;
    std::vector<std::vector<int>> board(n, vector<int>(n, 0));

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> board[i][j];

    vector<int> answer = NonaDivision(board, { 0, 0 }, { n - 1, n - 1 });

    for (int e : answer)
    {
        cout << e << endl;
    }

    return 0;
}
