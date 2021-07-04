
// 상태와 행동

// 상태공간트리 (State Space Tree) or (Game Tree)
// 상태공간트리는 문제의 가능한 모든 상태를 노드로 구성한 트리이다.
// (시뮬레이션 문제라고 표현하기도 하는 것 같다.)


#include <vector>
#include <bitset>
using namespace std;



// 틱택토
enum Mark
{
    Blank, O, X
};

vector<Mark> state(9);


// 미로찾기 
struct State
{
    int i, j;
};

vector<pair<int, int>> actions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };



// 식인종 가족 강건너기
typedef bitset<7> State;
State state;


// 체스
enum ChessSymbols
{
    None,
    WhiteKing, WhiteQueen, WhiteRook, WhiteBishop, WhiteKnight, WhitePawn,
    BlackKing, BlackQueen, BlackRook, BlackBishop, BlackKnight, BlackPawn
};

vector<vector<ChessSymbols>> state;
