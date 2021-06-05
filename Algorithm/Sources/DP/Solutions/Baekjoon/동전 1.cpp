
// 동전 1 (DP)
// https://www.acmicpc.net/status?user_id=insooneelife&problem_id=2293&from_mine=1

// 문제 풀이
// 점화식
// F(N, K) : N원을 K개의 동전 조합으로 채우는 경우의 수 (중복 사용)
// F(N, K) : 
// (K번째 동전을 더 이상 선택하지 않고 K - 1 번째 동전부터 채우는 경우의 수) + (K번째 동전을 선택하는 경우의 수)
// F(N, K) = F(N, K - 1) + F(N - Coin[i], K)

// 시행착오
// 1. 모든 동전에 대해 F(0, K) = 1 로 초기화
// 2. 아래 코드에는 문제가 있다.
/*
for (int i = 1; i <= k; ++i)
    for (int j = 0; j < n; ++j)
        if (i - coin[j] >= 0)
            D[i][j] += D[i][j - 1] + D[i - coin[j]][j];
        
점화식대로 계산한다면
F(1, 1) = F(1 - 2, 1) + F(1, 0) = F(1, 0) = 1
이어야 하는데,
위 코드대로면 F(1, 1)에 대한 처리 자체를 하지 않게 된다.
동전의 값이 N을 초과하는 경우는 예외처리를 해주어야 하지만, 동전을 선택하지 않는 경우는 유지되어야 한다.

for (int i = 1; i <= k; ++i)
    for (int j = 0; j < n; ++j)
        if (i - coin[j] >= 0)
            D[i][j] += D[i][j - 1] + D[i - coin[j]][j];
        else
            D[i][j] = D[i][j - 1];

*/
// 3. 메모리 초과, 메모리를 절약하는 방법을 생각해보자
// 메모리 초과 코드
/*
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
using ll = long long;

ll D[100001][101] = { 0 };

int main()
{
    int n, k;
    cin >> n >> k;

    vector<ll> coin(n, 0);
    for (int i = 0; i < n; ++i)
    {
        cin >> coin[i];
    }
    sort(begin(coin), end(coin));

    for (int i = 0; i < n; ++i)
    {
        D[0][i] = 1;
    }

    for (int i = 1; i <= k; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (i - coin[j] >= 0)
            {
                D[i][j] += D[i][j - 1] + D[i - coin[j]][j];
            }
            else
            {
                D[i][j] = D[i][j - 1];
            }
        }

    }

    cout << D[k][n] << endl;
    return 0;
}

위 코드가 메모리를 참조하는 방법은 다음과 같다.
■□□□□
□■□□□
□□■□□
□□□■□
■■■■□
□□□□□
□□□□□
□□□□□

그러므로 메모리의 값이 손실되지 않도록 절약하기 위해,
순회방법을 for 모든 행, for 모든 열 형태가 아니라,
for 모든 열, for 모든 행 형태로 수정해야한다. 
(한칸 이전에 대한 참조는 이전값을 통해 얻을 수 있지만, 여러 칸 이전값은 배열이 아니면 얻을 수 없기 때문)
*/




#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
using ll = long long;
ll D[100001] = { 0 };

int main()
{
    int n, k;
    cin >> n >> k;

    vector<ll> coin(n, 0);
    for (int i = 0; i < n; ++i)
    {
        cin >> coin[i];
    }
    sort(begin(coin), end(coin));

    D[0] = 1;
    for (int j = 0; j < n; ++j)
    {
        for (int i = 1; i <= k; ++i)
        {
            if (i - coin[j] >= 0)
            {
                D[i] += D[i - coin[j]];
            }
        }
        
    }
 
    ll ans = D[k] > 0 ? D[k] : -1;
    cout << ans << endl;
    return 0;
}

/*
3 10
1
2
5
*/