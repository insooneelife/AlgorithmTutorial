// 자물쇠와 열쇠
// https://programmers.co.kr/learn/courses/30/lessons/60059

// 문제해결
// 모든 회전(0, 90, 180, 270) * 모든 가능한 포지션(키가 자물쇠의 왼쪽위에 걸치는 위치부터 오른쪽 아래에 걸치는 위치까지) * 모든 키 홈 위치
// 위 경우로 만들어진 (키 홈 위치 리스트 == 자물쇠 홈 위치 리스트) 인 경우가 단 하나라도 존재하면 true, else false


// 시행착오
// 1. moves의 조합을 만들기 위해 조금 복잡하게 생각함 (단순 iterate으로 가능했는데, 실제 조합을 이용할뻔함) 
// 2. moves의 범위를 LockNum으로 이용하여야 했는데 KeyNum을 이용함
// 3. rotate 후 move를 해야 정상동작함. move 후 rotate을 하면 이상한 값이 만들어질 수 있음

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

//#include "Print.h"
using namespace std;

struct Pos
{
    Pos(int i, int j) : i(i), j(j) {}

    bool operator==(const Pos& other) const
    {
        return i == other.i && j == other.j;
    }

    bool operator<(const Pos& other) const
    {
        if (i == other.i)
            return j < other.j;
        return i < other.i;
    }

public:
    int i;
    int j;
};

void Rotate(int N, int rotates, Pos& pos)
{
    for (int r = 0; r < rotates; ++r)
    {
        int tempi = pos.i;
        int tempj = pos.j;
        pos.i = tempj;
        pos.j = N - 1 - tempi;
    }
}

bool InRange(int N, int i, int j)
{
    return 0 <= i && i < N && 0 <= j && j < N;
}

void Print(const vector<Pos>& v, string tag = "------------------------------------------")
{
    cout << tag << endl;
    for (Pos pos : v)
    {
        cout << "(" << pos.i << ", " << pos.j << ")  " << endl;
    }
    cout << endl;
}

bool solution(vector<vector<int>> key, vector<vector<int>> lock) 
{
    const int KeyNum = key.size();
    const int LockNum = lock.size();

    const vector<int> rotations = { 0, 1, 2, 3 };
    vector<Pos> moves;

    for (int i = -(KeyNum - 1); i <= (KeyNum - 1) + (LockNum - 1); ++i)
    {
        for (int j = -(KeyNum - 1); j <= (KeyNum - 1) + (LockNum - 1); ++j)
        {
            moves.push_back(Pos(i, j));
        }
    }

    vector<Pos> pos_key;
    vector<Pos> pos_lock;

    for (int i = 0; i < KeyNum; ++i)
    {
        for (int j = 0; j < KeyNum; ++j)
        {
            if (key[i][j] == 1)
            {
                pos_key.push_back(Pos(i, j));
            }
        }
    }

    for (int i = 0; i < LockNum; ++i)
    {
        for (int j = 0; j < LockNum; ++j)
        {
            if (lock[i][j] == 0)
            {
                pos_lock.push_back(Pos(i, j));
            }
        }
    }
    
    sort(begin(pos_lock), end(pos_lock));
    //Print(pos_lock, "-------------------lock-------------------");

    // all movements
    for (Pos move : moves)
    {
        int movei = move.i;
        int movej = move.j;

        // all rotations
        for (int rotates : rotations)
        {
            vector<Pos> candidate_key;

            // all key positions
            for (Pos pos : pos_key)
            {
                Rotate(KeyNum, rotates, pos);
                pos = Pos(pos.i + movei, pos.j + movej);
                    
                if (InRange(LockNum, pos.i, pos.j))
                {
                    candidate_key.push_back(pos);
                }
            }

            // test
            sort(begin(candidate_key), end(candidate_key));
            //Print(candidate_key);

            if (candidate_key == pos_lock)
            {
                return true;
            }
        }
    }

    return false;
}


int main()
{
    vector<vector<int>> key =
    {
        {0, 0, 0},
        {1, 0, 0},
        {0, 1, 1}
    };

    vector<vector<int>> lock =
    {
        {1, 1, 1},
        {1, 1, 0},
        {1, 0, 1}
    };


    bool answer = solution(key, lock);

    cout << answer;

    return 0;

}