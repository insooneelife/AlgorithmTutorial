
// 부분배열 고르기 (분할정복)
// https://www.acmicpc.net/problem/2104

// 시행착오
// 1. int 오버플로우 -> long long 사용

// 문제 해결
// 6
// 3 1 6 4 5 2

// 왼쪽 부분문제
// 3 1 6 의 최대점수는 구했다고 가정

// 오른쪽 부분문제
// 4 5 2 의 최대점수는 구했다고 가정

// 왼쪽과 오른쪽을 모두 걸쳐서 만들어지는 부분배열들 중,
// 쓸만한 후보들 검사 O(N)
// 6 4          최대점수 (6 + 4) * 4  {6, 4}의 현재까지의 최소값, 합
// 6 4 5        {1, 5} 중, 5 선택 -> 최대점수를 구함 -> 최종 점수 갱신              -> {6, 4, 5}의 최소값, 합 (델타값만 활용하여 현재까지의 값 갱신)
// 6 4 5 2      {1, 2} 중, 2 선택 -> 최대점수를 구함 -> 최종 점수 갱신              -> {6, 4, 5, 2}의 최소값, 합 (델타값만 활용) 
// 1 6 4 5 2    오른쪽 구간이 끝났으므로 1 선택 -> 최대점수를 구함 -> 최종 점수 갱신   -> {1, 6, 4, 5, 2}의 최소값, 합 (델타값만 활용)
// 3 1 6 4 5 2  오른쪽 구간이 끝났으므로 3 선택 -> 최대점수를 구함 -> 최종 점수 갱신   -> {3, 1, 6, 4, 5, 2}의 최소값, 합 (델타값만 활용)

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

    // 후보들 나열 후 검사 O(N)
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


    // 부분문제 1.
    // 왼쪽 배열의 최대점수를 반환한다.
    ll lscore = MaxScore(scores, sum, from, mid);

    // 부분문제 2.
    // 오른쪽 배열의 최대점수를 반환한다.
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