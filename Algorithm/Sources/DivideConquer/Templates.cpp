
// 2차원 배열을 4개의 공간으로 분할
static void QuadDivision(std::vector<std::vector<int>>& board, Idx from, Idx to)
{
    using namespace std;
    // length 
    const int N = (to.i - from.i) + 1;
    if (N == 1)
        return;

    int mi = from.i + N / 2 - 1;
    int mj = from.j + N / 2 - 1;

    vector<pair<Idx, Idx>> from_to =
    {
        {from, {mi, mj}},                   // left, top
        {{from.i, mj + 1}, {mi, to.j}},     // right, top
        {{mi + 1, from.j}, {to.i, mj}},     // left, bottom
        {{mi + 1, mj + 1}, {to.i, to.j}}    // right, bottom
    };

    for (const auto& e : from_to)
    {
        QuadDivision(board, e.first, e.second);
    }
}


// 히스토그램에서 가장 큰 정사각형
long long MaxRectSize(const vector<long long>& histo, long long from, long long to)
{
    using ll = long long;
    if (from == to)
        return histo[from];

    ll mid = (from + to) / 2;
    ll minheight = min(histo[mid], histo[mid + 1]);
    ll left = mid;
    ll right = mid + 1;
    ll maxsize = max(maxsize, minheight * (right - left + 1));

    while (from < left || right < to)
    {
        if (right < to && (left == from || histo[left - 1] < histo[right + 1]))
        {
            right++;
            minheight = min(minheight, histo[right]);
        }
        else
        {
            left--;
            minheight = min(minheight, histo[left]);
        }

        maxsize = max(maxsize, minheight * (right - left + 1));
    }

    ll lmax = MaxRectSize(histo, from, mid);
    ll rmax = MaxRectSize(histo, mid + 1, to);
    maxsize = max(maxsize, max(lmax, rmax));

    return maxsize;
}

long long MaxRectSizeInHistogram(const vector<long long>& histo)
{
    return MaxRectSize(histo, 0, histo.size() - 1);
}