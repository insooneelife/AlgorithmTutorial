
// 최대 직사각형
// https://www.acmicpc.net/problem/11873

// 시행착오
// 1. 입출력 속도로 인한 시간초과
// 다음 코드로 해결
// ios_base::sync_with_stdio(false);
// cin.tie(NULL);
// cout.tie(NULL);

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
//#include "Print.h"

using namespace std;
using ll = long long;

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



ll MaxRectSize(const vector<vector<ll>>& board)
{
    const int R = board.size();
    const int C = board[0].size();
    vector<vector<ll>> histograms(begin(board), end(board));

    // make histograms for all rows
    for (int i = 1; i < R; ++i)
    {
        for (int j = 0; j < C; ++j)
        {
            if (histograms[i][j] == 0)
                histograms[i][j] = 0;
            else
                histograms[i][j] += histograms[i - 1][j];
        }
    }

    ll maxsize = 0;
    for (const vector<ll>& histogram : histograms)
    {
        maxsize = max(maxsize, MaxRectSizeInHistogram(histogram));
    }

    return maxsize;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    while (true)
    {
        int R, C;
        cin >> R >> C;

        if (R == 0 && C == 0)
            break;

        vector<vector<ll>> board(R, vector<ll>(C));

        for (int i = 0; i < R; ++i)
        {
            for (int j = 0; j < C; ++j)
            {
                cin >> board[i][j];
            }
        }

        cout << MaxRectSize(board) << endl;
    }

    return 0;
}
