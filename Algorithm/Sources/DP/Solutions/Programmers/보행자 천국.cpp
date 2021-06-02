
// 보행자 천국 (DP)
// https://programmers.co.kr/learn/courses/30/lessons/1832

// 1. 전역 변수 선언 시, 함수 내에 초기화 코드를 작성해야함
// 2. 문제에서 방향 정보를 요구하므로, 방향에 대한 인자를 추가하여야 하는데, 두 가지 방법이 있다.
// 방법 1. F(i, j, d) = d 방향으로 i, j 위치에 오는 경우의 수
// 방법 2. F(i, j, d) = i, j 위치에서 d 방향으로 가는 경우의 수

// 첫번째 방법의 경우, F(i, j, d)를 통해 작업을 할 때 이전 상태에서 어느 방향으로 현재 상태에 오게 되었는지를 통해 만들어진 점화식이다.
// 그러므로 방향제한이 있는 정보를 처리할 때, 이전 배열판 map[i - 1][j] or map[i][j - 1]을 참조해야하므로 코드가 복잡해질 수 있다.

// 두번째 방법의 경우, F(i, j, d)로부터 어느 방향으로 나가는지에 대한 경우의 수를 계산하도록 설계된 점화식이다.
// 조금 더 깔끔하게 구현이 가능하다.


#include <vector>
#include <iostream>
using namespace std;
using ll = long long;

const ll MOD = 20170805;
const ll Right = 0;
const ll Down = 1;
const ll Blocked = 1;
const ll Directed = 2;

ll mem[500][500][2] = { 0 };
bool visited[500][500][2] = { false };

// i,j 위치에서 dir 방향으로 이동할 수 있는 경우의 수
ll F(const vector<vector<int>>& map, ll i, ll j, ll dir)
{
    if (i < 0 || j < 0)
        return 0;

    if (i == 0 && j == 0)
        return 1;
    
    if (visited[i][j][dir])
        return mem[i][j][dir];

    visited[i][j][dir] = true;

    ll ret = 0;
    if (map[i][j] == Blocked)
    {
        ret = 0;
    }
    else
    {
        if (map[i][j] == Directed)
        {
            if (dir == Right)
            {
                ret = F(map, i, j - 1, Right);
            }
            else
            {
                ret = F(map, i - 1, j, Down);
            }
        }
        else
        {
            ret = (F(map, i, j - 1, Right) % MOD + F(map, i - 1, j, Down) % MOD) % MOD;
        }
    }

    return mem[i][j][dir] = ret;
    
}


// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
int solution(int m, int n, vector<vector<int>> city_map) 
{
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            for (int k = 0; k < 2; ++k)
            {
                mem[i][j][k] = 0;
                visited[i][j][k] = false;
            }
        }
    }

    return F(city_map, m - 1, n - 1, Right);
}


int main() 
{
    /*
    int m = 3;
    int n = 3;
    vector<vector<int>> city_map = 
    {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0} 
    };
    */
    
    
    int m = 3;
    int n = 3;
    vector<vector<int>> city_map =
    {
        {0, 2, 0, 0, 0, 2},
        {0, 0, 2, 0, 1, 0},
        {1, 0, 0, 2, 2, 0}
    };
    


    cout << solution(m, n, city_map) << endl;

    return 0;
}
