
// 리틀 프렌즈 사천성 (Brute Force)
// https://programmers.co.kr/learn/courses/30/lessons/1836

// 시행착오
// 1. 너무 어렵게 생각하여 BFS로 접근함 (사천성의 꺽는 횟수가 최대 한번이므로 완전탐색으로도 가능함)
// 2. CanReach 함수의 너무 많은 코드가 들어가서 버그를 잡기 어려웠음
// 3. CanReachByDirection 함수로 모듈화한 후,
// for (Vec2i v = from + dir; v != to; v = v + dir) 에서 v != to 라는 조건은 v == to 인 상태에 대한 검사를 하지 않음
// 검사 후 break로 수정함
// 4. CanReachByDirection 함수가 true false만 리턴한다면, x로 먼저 이동해보고 y로 이동해보는 상황에 대한 테스트가 불가능함
// CanReachByDirection 함수의 리턴을 True, False, NotFound로 나누고, 
// x로 먼저 이동해보고 y로 이동해보는 상황은 x == NotFound && y == True 로 표현함
// 5. answer의 크기가 전체 알파벳의 크기와 같지 않다면 IMPOSSIBLE (answer의 size가 0 인지만 테스트하면 예외가 발생함)
// 6. 알파벳 출력순서를 위해, 한번이라도 사천성 컴포넌트를 제거했다면 break문을 통해 다시 초기 알파벳부터 시도할수 있도록 함

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <map>
//#include "Print.h"
using namespace std;

template<typename T>
struct Vec
{
    Vec() : x(0), y(0) {}
    Vec(int x, int y) : x(x), y(y) {}

public:
    bool operator==(const Vec& other) const
    {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Vec& other) const
    {
        return !(*this == other);
    }

    bool operator<(const Vec& other) const
    {
        if (x == other.x)
        {
            return y < other.y;
        }

        return x < other.x;
    }

    // for greater
    bool operator>(const Vec& other) const
    {
        if (x == other.x)
            return y > other.y;

        return x > other.x;
    }

    Vec operator+(const Vec& other) const
    {
        return Vec(x + other.x, y + other.y);
    }

    Vec operator-(const Vec& other) const
    {
        return Vec(x - other.x, y - other.y);
    }

    // unary minus
    Vec operator- ()
    {
        return Vec(-x, -y);
    }

public:
    T x;
    T y;
};

using Vec2i = Vec<int>;

struct State
{
    int i, j, cnt;
};

static bool InArray2D(int rows, int columns, int i, int j)
{
    return
        0 <= i && i < rows &&
        0 <= j && j < columns;
}

static bool IsUppercase(char c)
{
    return 'A' <= c && c <= 'Z';
}

int ManhatanDis(Vec2i a, Vec2i b)
{
    return abs(a.x - b.x) + abs(a.y - b.y);
}

const int False = -1;
const int True = 1;
const int NotFound = 0;

int CanReachByDirection(const vector<string>& board, Vec2i from, Vec2i to, char type, Vec2i dir)
{
    for (Vec2i v = from + dir; ; v = v + dir)
    {
        //cout <<type << "   v : " << v.x << " " << v.y << "  to : " << to.x << " " << to.y << "  dir : " << dir.x << " " << dir.y << endl;
        if (board[v.x][v.y] == type)
            return True;
        
        if (board[v.x][v.y] != '.')
            return False;

        if (v == to)
            break;
    }

    return NotFound;
}

bool CanReach(const vector<string>& board, Vec2i from, Vec2i to, char type)
{
    // true if two are adjoined
    int distance = ManhatanDis(from, to);
    if (distance == 1)
    {
        return true;
    }

    Vec2i totarget = (to - from);
    int movex = (totarget.x != 0) ? (totarget.x / abs(totarget.x)) : 0;
    int movey = (totarget.y != 0) ? (totarget.y / abs(totarget.y)) : 0;
    Vec2i xdir = { movex, 0 };
    Vec2i ydir = { 0, movey };

    if (movey == 0)
    {
        if (CanReachByDirection(board, from, { to.x, from.y }, type, xdir) == True)
            return true;
    }
    
    else if (movex == 0)
    {
        if (CanReachByDirection(board, from, { from.x, to.y }, type, ydir) == True)
            return true;
    }
    else
    {
        int xmove_result = CanReachByDirection(board, from, { to.x, from.y }, type, xdir);
        int ymove_result = CanReachByDirection(board, { to.x, from.y }, to, type, ydir);
        if (xmove_result == True || (xmove_result == NotFound && ymove_result == True))
            return true;

        ymove_result = CanReachByDirection(board, from, { from.x, to.y }, type, ydir);
        xmove_result = CanReachByDirection(board, { from.x, to.y }, to, type, xdir);
        if (ymove_result == True || (ymove_result == NotFound && xmove_result == True))
            return true;
    }

    return false;
}

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
string solution(int m, int n, vector<string> board)
{
    // make pair positions
    map<char, vector<Vec2i>> dests;
    for (int i = 0; i < board.size(); ++i)
    {
        for (int j = 0; j < board[i].size(); ++j)
        {
            char c = board[i][j];
            if (IsUppercase(c))
            {
                auto it = dests.find(c);
                if (it != end(dests))
                {
                    it->second.push_back({ i, j });
                }
                else
                {
                    vector<Vec2i> v = { {i, j} };
                    dests.insert(make_pair(c, v));
                }
            }
        }
    }
    int answer_len = dests.size();

    //Print::ContainerInContainer(board);

    vector<char> removed;
    removed.reserve(26);

    for (int i = 0; i < 26; ++i)
    {
        for (auto e : dests)
        {
            char type = e.first;
            Vec2i from = e.second[0];
            Vec2i to = e.second[1];

            // remove if can reach from -> to
            if (CanReach(board, from, to, type))
            {
                board[from.x][from.y] = '.';
                board[to.x][to.y] = '.';
                removed.push_back(type);
                break;
            }

            //Print::ContainerInContainer(board);
        }

        for (char c : removed)
        {
            dests.erase(c);
        }
    }

    string answer = "";
    for(char c : removed)
    {
        answer += c;
    }
    return (answer.size() == answer_len) ? answer : "IMPOSSIBLE";
}

int main()
{
    //int m = 3;
    //int n = 3;
    //vector<string> board = { "DBA", "C*A", "CDB" };

    //int m = 2;
    //int n = 4;
    //vector<string> board = { "NRYN", "ARYA" };

    //int m = 4;
    //int n = 4;
    //vector<string> board = { ".ZI.", "M.**", "MZU.", ".IU." };

    //int m = 2;
    //int n = 2;
    //vector<string> board = { "AB", "BA" };

    int m = 5;
    int n = 5;
    vector<string> board = { "FGHEI", "BAB..", "D.C*.", "CA..I", "DFHGE" };
    // answer : ABCDFHGIE

    cout << solution(m, n, board);

    return 0;
}