// 블록 이동하기 (BFS)
// https://programmers.co.kr/learn/courses/30/lessons/60063

// 시행착오
// DirectionsCCW 에 잘못된 값이 들어가 있었음

// Move에서 특정 방향일 때 선별적으로 SetBoard를 해줄 필요가 없었음 (시간 조금 낭비)

// IsParallel과 IsOpposite은 사용된적이 없음

// GetState()에서 sort를 해주는것은 상태를 파괴하는 일이었음 (원래는 상태의 정규화를 목표로 했지만, left와 right의 순서도 상태에 영향을 주는 것임)

// robot의 미래 State을 알고 visited에서 검사 후 움직여야하는데, 그러려면 로봇을 직접 움직여야한다. 
// 그리고 로봇이 움직이려면 먼저 CanMove로 체크를 해야한다. (문제가 되는 부분은 CanMove와 visited 검사를 동시에 하려고 해서 발생함.)

// 사실 로봇에서 SetBoard는 필요가 없음 (디버깅 외에는 의미가 없음)

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <bitset>
#include <functional>
#include <sstream>

//#include "Print.h"
//#include "Utility.h"

using namespace std;

const int N = 102;
int board[N][N] = {};
using namespace std;

enum class Types
{
    Blank, Wall, Robot
};

enum class RotateAxis
{
    Left, Right
};

bool InArray2D(int n, int a, int b)
{
    return  0 <= a && a < n && 0 <= b && b < n;
}

struct Vec
{
    Vec(int i, int j) : i(i), j(j) {}

public:
    bool operator==(const Vec& other) const
    {
        return i == other.i && j == other.j;
    }

    bool operator<(const Vec& other) const
    {
        if (i == other.i)
        {
            return j < other.j;
        }

        return i < other.i;
    }

    Vec operator+(const Vec& other) const
    {
        return Vec(i + other.i, j + other.j);
    }

    Vec operator-(const Vec& other) const
    {
        return Vec(i - other.i, j - other.j);
    }

    // unary minus
    Vec operator- ()
    {
        return Vec(-i, -j);
    }

public:
    int i;
    int j;
};

const vector<Vec> DirectionsCCW = { { 0, 1 }, { -1, 0 }, { 0, -1 }, { 1, 0 } };
const vector<pair<RotateAxis, int>> Rotations =
{
    {RotateAxis::Left, 1}, {RotateAxis::Left, -1}, {RotateAxis::Right, 1}, {RotateAxis::Right, -1}
};


struct Robot
{
    Robot(vector<vector<int>>& board, Vec left, Vec right)
        :
        N(board.size()), board(board), left(left), right(right)
    {
        SetBoard(left, Types::Robot);
        SetBoard(right, Types::Robot);
    }

    ~Robot()
    {
        SetBoard(left, Types::Blank);
        SetBoard(right, Types::Blank);
    }

public:
    void Move(Vec direction)
    {
        SetBoard(left, Types::Blank);
        SetBoard(right, Types::Blank);
        SetBoard(left + direction, Types::Robot);
        SetBoard(right + direction, Types::Robot);

        left = left + direction;
        right = right + direction;
    }

    void Rotate(RotateAxis axis, int rotates)
    {
        if (axis == RotateAxis::Left)
        {
            RotateAxis(left, right, rotates);
        }
        else
        {
            RotateAxis(right, left, rotates);
        }
    }

    // left to right direction
    Vec Direction() const
    {
        return Vec(right.i - left.i, right.j - left.j);
    }

    bool IsParallel(Vec direction) const
    {
        return Direction() == direction || IsOpposite(direction);
    }

    bool IsOpposite(Vec direction) const
    {
        return Direction() == -direction;
    }

    bool CanRotate(RotateAxis axis, int rotates) const
    {
        if (axis == RotateAxis::Left)
        {
            return CanRotate(left, right, rotates);
        }
        else
        {
            return CanRotate(right, left, rotates);
        }
    }


    bool CanMove(Vec direction) const
    {
        return CheckPos(left + direction) && CheckPos(right + direction);
    }

    bool CheckPos(Vec pos) const
    {
        return InArray2D(N, pos.i, pos.j) && board[pos.i][pos.j] != 1;
    }

    void SetBoard(Vec pos, Types val)
    {
        board[pos.i][pos.j] = (int)val;
    }

    Types GetBoard(Vec pos) const
    {
        return (Types)board[pos.i][pos.j];
    }

    vector<Vec> GetState() const
    {
        vector<Vec> vec = { left, right };
        return vec;
    }

    bool HasArrived(Vec pos) const
    {
        return left == pos || right == pos;
    }

    void Print(string additional) const
    {
        Vec direction = Direction();
        cout << additional << endl;
        cout << "left : " << left.i << " " << left.j << "  right : " << right.i << " " << right.j << "  direction : " << direction.i << " " << direction.j << endl;
        //Print::ContainerInContainer(board, "");
    }

private:

    void RotateAxis(Vec axis_pos, Vec& target_pos, int rotates)
    {
        Vec prev = target_pos;
        Vec next = GetRotatedPos(axis_pos, target_pos, rotates);

        SetBoard(prev, Types::Blank);
        SetBoard(next, Types::Robot);

        target_pos = next;
    }

    // rotates must be -1 or 1
    bool CanRotate(Vec axis_pos, Vec target_pos, int rotates) const
    {
        Vec rotated_pos = GetRotatedPos(axis_pos, target_pos, rotates);

        // target   axis
        // test     rotated
        Vec test_pos = target_pos + rotated_pos - axis_pos;

        return CheckPos(rotated_pos) && CheckPos(test_pos);
    }

    Vec GetRotatedPos(Vec axis_pos, Vec target_pos, int rotates) const
    {
        Vec direction = GetRotateDirection(axis_pos, target_pos, rotates);
        return axis_pos + direction;
    }

    // -4 <= rotates <= 4
    static Vec GetRotateDirection(Vec axis_pos, Vec target_pos, int rotates)
    {
        Vec direction = target_pos - axis_pos;
        int index = GetDirectionCCWIndex(direction);
        int size = DirectionsCCW.size();
        // ccw
        Vec rotated_direction = DirectionsCCW[(index + rotates + size) % size];

        return rotated_direction;
    }

    static int GetDirectionCCWIndex(Vec direction)
    {
        int index = -1;
        for (int i = 0; i < DirectionsCCW.size(); ++i)
        {
            if (DirectionsCCW[i] == direction)
            {
                index = i;
                return index;
            }
        }
        // assumes never get here
        return index;
    }

private:
    int N;
    vector<vector<int>>& board;
    Vec left;
    Vec right;
};

struct State
{
    int cost;
    vector<Vec> positions;

    State(vector<Vec> positions, int cost)
        :
        cost(cost),
        positions(positions)
    {}
};

int BFS(vector<vector<int>>& board, Vec start, Vec finish)
{
    set<vector<Vec>> visited;
    queue<State> que;
    Robot robot(board, start, Vec(start.i, start.j + 1));

    int cost = 0;
    auto state = robot.GetState();
    que.push(State(state, 0));
    visited.insert(state);

    while (!que.empty())
    {
        State s = que.front();
        cost = s.cost;

        Robot robot(board, s.positions[0], s.positions[1]);

        // move actions
        for (int i = 0; i < DirectionsCCW.size(); ++i)
        {
            Robot robot(board, s.positions[0], s.positions[1]);
            Vec direction = DirectionsCCW[i];

            if (robot.CanMove(direction))
            {
                robot.Move(direction);

                if (visited.find(robot.GetState()) == end(visited))
                {
                    que.push(State(robot.GetState(), cost + 1));
                    visited.insert(robot.GetState());
                }
            }
        }

        // rotate actions
        for (int i = 0; i < DirectionsCCW.size(); ++i)
        {
            Robot robot(board, s.positions[0], s.positions[1]);

            pair<RotateAxis, int> rotation = Rotations[i];
            RotateAxis axis = rotation.first;
            int rotates = rotation.second;

            if (robot.CanRotate(axis, rotates))
            {
                robot.Rotate(axis, rotates);

                if (visited.find(robot.GetState()) == end(visited))
                {
                    que.push(State(robot.GetState(), cost + 1));
                    visited.insert(robot.GetState());
                }
            }
        }

        if (robot.HasArrived(finish))
        {
            break;
        }

        que.pop();
    }

    return cost;
}

int solution(vector<vector<int>> board)
{
    const int n = board.size();
    Vec start(0, 0);
    Vec finish(n - 1, n - 1);

    return BFS(board, start, finish);
}


int main()
{
    vector<vector<int>> board =
    {
        { 0, 0, 0, 1, 1 },
        { 0, 0, 0, 1, 0 },
        { 0, 1, 0, 1, 1 },
        { 1, 1, 0, 0, 1 },
        { 0, 0, 0, 0, 0 }
    };

    int answer = solution(board);

    //Print::ContainerInContainer(board);


    return 0;
}

