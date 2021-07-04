
// ���¿� �ൿ

// ���°���Ʈ�� (State Space Tree) or (Game Tree)
// ���°���Ʈ���� ������ ������ ��� ���¸� ���� ������ Ʈ���̴�.
// (�ùķ��̼� ������� ǥ���ϱ⵵ �ϴ� �� ����.)


#include <vector>
#include <bitset>
using namespace std;



// ƽ����
enum Mark
{
    Blank, O, X
};

vector<Mark> state(9);


// �̷�ã�� 
struct State
{
    int i, j;
};

vector<pair<int, int>> actions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };



// ������ ���� ���ǳʱ�
typedef bitset<7> State;
State state;


// ü��
enum ChessSymbols
{
    None,
    WhiteKing, WhiteQueen, WhiteRook, WhiteBishop, WhiteKnight, WhitePawn,
    BlackKing, BlackQueen, BlackRook, BlackBishop, BlackKnight, BlackPawn
};

vector<vector<ChessSymbols>> state;
