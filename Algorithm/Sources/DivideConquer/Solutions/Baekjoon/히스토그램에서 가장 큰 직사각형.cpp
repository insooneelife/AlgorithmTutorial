
// 히스토그램에서 가장 큰 직사각형
// https://www.acmicpc.net/problem/6549

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

ll MaxSize(const vector<ll>& histo, ll from, ll to)
{
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

    ll lmax = MaxSize(histo, from, mid);
    ll rmax = MaxSize(histo, mid + 1, to);
    maxsize = max(maxsize, max(lmax, rmax));

    return maxsize;
}

int main()
{
    while (true)
    {
        int n;
        cin >> n;

        if (n == 0)
            break;

        vector<ll> histo;
        histo.reserve(n);

        for (int i = 0; i < n; ++i)
        {
            ll h;
            cin >> h;
            histo.push_back(h);
        }

        ll ans = MaxSize(histo, 0, histo.size() - 1);
        cout << ans << endl;
    }
    

    return 0;
}
