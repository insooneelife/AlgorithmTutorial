// 쿼드압축 후 개수 세기
// https://programmers.co.kr/learn/courses/30/lessons/68936

#include <vector>
#include <iostream>
using namespace std;

const vector<int> one = { 0, 1 };
const vector<int> zero = { 1, 0 };

vector<int> AddVec(const vector<int>& a, const vector<int>& b)
{
    vector<int> c(a.size(), 0);
    for (int i = 0; i < a.size(); ++i)
    {
        c[i] = a[i] + b[i];
    }
    return c;
}

vector<int> Quadtree(const vector<vector<int>>& arr, int si, int sj, int ei, int ej)
{
    if (si == ei)
        return arr[si][sj] == 0 ? zero : one;

    const int N = (ei - si) + 1;
    int mi = si + N / 2 - 1;
    int mj = sj + N / 2 - 1;

    vector<int> lt = Quadtree(arr, si, sj, mi, mj);
    vector<int> rt = Quadtree(arr, si, mj + 1, mi, ej);
    vector<int> lb = Quadtree(arr, mi + 1, sj, ei, mj);
    vector<int> rb = Quadtree(arr, mi + 1, mj + 1, ei, ej);

    if (lt == one && lt == rt && lt == lb && lt == rb)
        return one;

    if (lt == zero && lt == rt && lt == lb && lt == rb)
        return zero;

    return AddVec(AddVec(lt, rt), AddVec(lb, rb));
}


vector<int> solution(vector<vector<int>> arr) 
{
    const int N = arr.size();
    return Quadtree(arr, 0, 0, N - 1, N - 1);
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

