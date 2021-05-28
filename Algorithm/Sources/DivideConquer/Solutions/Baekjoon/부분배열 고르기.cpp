
// 부분배열 고르기 (분할정복)
// https://www.acmicpc.net/problem/2104

// 시행착오
// 1. int 오버플로우 -> long long 사용

#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

// MaxScore는 [from, to] 범위의 부분배열들 중 최대의 점수를 반환한다.
// MaxScore(from, to)는
// MaxScore(from, mid), MaxScore(mid + 1, to), 가운데 2개 원소를 포함하는 최대점수의 부분배열 중 최대점수를 반환.
ll MaxScore(const vector<ll>& scores, const vector<ll>& sum, int from, int to)
{
    if (from == to)
        return scores[from] * scores[from];
    
    const int mid = from + (to - from) / 2;

    int left = mid;
    int right = mid + 1;
    ll minscore = min(scores[left], scores[right]);
    ll finalscore = (scores[left] + scores[right]) * minscore;

    while (from < left || right < to)
    {
        if (right < to && (left == from || scores[left - 1] < scores[right + 1]))
        {
            right++;
            minscore = min(minscore, scores[right]);
        }
        else
        {
            left--;
            minscore = min(minscore, scores[left]);
        }

        ll rangesum = sum[right] - sum[left - 1];
        finalscore = max(finalscore, rangesum * minscore);
    }


    ll lscore = MaxScore(scores, sum, from, mid);
    ll rscore = MaxScore(scores, sum, mid + 1, to);
    finalscore = max(finalscore, lscore);
    finalscore = max(finalscore, rscore);
    return finalscore;
}

int main()
{
    int n;
    cin >> n;
    vector<ll> scores(n + 1);
    vector<ll> sum(n + 1, 0);

    for (int i = 1; i <= n; ++i)
    {
        cin >> scores[i];
        sum[i] = sum[i - 1] + scores[i];
    }

    ll ans = MaxScore(scores, sum, 1, scores.size() - 1);
    cout << ans << endl;

    return 0;
}