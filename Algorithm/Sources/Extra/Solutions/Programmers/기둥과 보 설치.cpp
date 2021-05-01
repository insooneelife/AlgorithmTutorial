
// 기둥과 보 설치
// https://programmers.co.kr/learn/courses/30/lessons/60061

// 시행착오
// xy 좌표계와 2차원 배열 인덱스의 차이로 인한 예외 발생
// Get, Set으로 변환과정중 실수 발생
// 구조물 파괴 시에 x, y 위치의 구조물에 대한 테스트를 진행함 -> x, y 건물이 아니라 그 주변 구조물에 대해 테스트 해야 함
// 구조물 파괴 시에 x, y 의 범위값 검사가 유효하지 않다면, 검사 자체를 하지 않아야 함
// 구조물 파괴 시에 x, y 위치에 파괴대상 구조물이 없다면, 검사 자체를 하지 않아야 함

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include "Print.h"

using namespace std;

enum class Type
{
    Pillar, Floor, None
};

enum class How
{
    Destruct, Construct
};

int N = 0;
Type pillars[101][101] = {};
Type floors[101][101] = {};

void Set(Type board[101][101], int x, int y, Type val)
{
    board[N - y][x] = val;
}

Type Get(Type board[101][101], int x, int y)
{
    return board[N - y][x];
}

void Print(Type board[101][101])
{
    for (int x = 0; x <= N; ++x)
    {
        for (int y = 0; y <= N; ++y)
        {
            cout << (int)Get(board, x, y) << " ";
        }
        cout << endl;
    }
    cout << endl;
}

bool InRange(int x, int y)
{
    return  0 <= x && x <= N && 0 <= y && y <= N;
}

bool IsPillar(int x, int y)
{
    return Get(pillars, x, y) == Type::Pillar;
}

bool IsFloor(int x, int y)
{
    return Get(floors, x, y) == Type::Floor;
}

bool CanConstructPillar(int x, int y)
{
    if (y == 0)
    {
        return true;
    }

    if (IsPillar(x, y - 1))
    {
        return true;
    }

    if (IsFloor(x - 1, y))
    {
        return true;
    }

    if (IsFloor(x, y))
    {
        return true;
    }

    return false;
}

bool CanConstructFloor(int x, int y)
{
    if (IsPillar(x, y - 1))
    {
        return true;
    }

    if (IsPillar(x + 1, y - 1))
    {
        return true;
    }

    if (IsFloor(x - 1, y) && IsFloor(x + 1, y))
    {
        return true;
    }

    return false;
}

bool CanDestructPillar(int x, int y)
{
    Type save = Get(pillars, x, y);

    Set(pillars, x, y, Type::None);

    bool test = true;
    if (InRange(x, y + 1) && IsPillar(x, y + 1))
    {
        test = test && CanConstructPillar(x, y + 1);
    }

    if (InRange(x - 1, y + 1) && IsFloor(x - 1, y + 1))
    {
        test = test && CanConstructFloor(x - 1, y + 1);
    }

    if (InRange(x, y + 1) && IsFloor(x, y + 1))
    {
        test = test && CanConstructFloor(x, y + 1);
    }

    Set(pillars, x, y, save);

    return test;
}

bool CanDestructFloor(int x, int y)
{
    Type save = Get(floors, x, y);
    Set(floors, x, y, Type::None);

    bool test = true;
    if (InRange(x, y) && IsPillar(x, y))
    {
        test = test && CanConstructPillar(x, y);
    }

    if (InRange(x + 1, y) && IsPillar(x + 1, y))
    {

        test = test && CanConstructPillar(x + 1, y);
    }

    if (InRange(x - 1, y) && IsFloor(x - 1, y))
    {
        test = test && CanConstructFloor(x - 1, y);
    }

    if (InRange(x + 1, y) && IsFloor(x + 1, y))
    {

        test = test && CanConstructFloor(x + 1, y);
    }

    Set(floors, x, y, save);

    return test;
}


void Construct(int x, int y, Type type)
{
    if (type == Type::Pillar)
    {
        if (CanConstructPillar(x, y))
        {
            Set(pillars, x, y, Type::Pillar);
        }
    }
    else
    {
        if (CanConstructFloor(x, y))
        {
            Set(floors, x, y, Type::Floor);
        }
    }
}

void Destruct(int x, int y, Type type)
{
    if (type == Type::Pillar)
    {
        if (CanDestructPillar(x, y))
        {
            Set(pillars, x, y, Type::None);
        }
    }
    else
    {
        if (CanDestructFloor(x, y))
        {
            Set(floors, x, y, Type::None);
        }
    }
}

void Process(const vector<int>& command)
{
    int x = command[0];
    int y = command[1];
    Type type = (Type)command[2];
    How how = (How)command[3];

    if (how == How::Construct)
    {
        Construct(x, y, type);
    }
    else
    {
        Destruct(x, y, type);
    }

    //Print(pillars);
}

vector<vector<int>> solution(int n, vector<vector<int>> build_frame)
{
    N = n;

    for (int x = 0; x <= N; ++x)
    {
        for (int y = 0; y <= N; ++y)
        {
            Set(floors, x, y, Type::None);
            Set(pillars, x, y, Type::None);
        }
    }

    for (const vector<int>& command : build_frame)
    {
        Process(command);
    }

    vector<vector<int>> answer;
    for (int x = 0; x <= N; ++x)
    {
        for (int y = 0; y <= N; ++y)
        {
            if (IsPillar(x, y))
            {
                answer.push_back({ x, y, (int)Type::Pillar });
            }

            if (IsFloor(x, y))
            {
                answer.push_back({ x, y, (int)Type::Floor });
            }
        }
    }

    sort(begin(answer), end(answer));

    return answer;
}


int main()
{
    /*
    int n = 5;
    vector<vector<int>> build_frame =
    {
        {1, 0, 0, 1}, {1, 1, 1, 1}, {2, 1, 0, 1}, {2, 2, 1, 1}, {5, 0, 0, 1}, {5, 1, 0, 1}, {4, 2, 1, 1}, {3, 2, 1, 1}
    };
    */


    int n = 5;
    vector<vector<int>> build_frame =
    {
        {0,0,0,1}, {2,0,0,1}, {4,0,0,1}, {0,1,1,1}, {1,1,1,1}, {2,1,1,1}, {3,1,1,1}, {2,0,0,0}, {1,1,1,0}, {2,2,0,1}
    };



    vector<vector<int>> answer = solution(n, build_frame);

    Print::ContainerInContainer(answer);

    return 0;
}