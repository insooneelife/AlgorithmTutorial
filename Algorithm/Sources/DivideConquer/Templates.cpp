
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