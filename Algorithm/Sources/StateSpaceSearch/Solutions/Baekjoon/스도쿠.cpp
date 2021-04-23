// 스도쿠 (백트래킹)
// https://www.acmicpc.net/problem/2580

// 시행착오
// vector의 push_back이 시간초과의 원인이 될 수 있음

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <map>
#include <list>

using namespace std; 

struct Data
{
    Data() : i(0), j(0) {}
    Data(int i, int j) : i(i), j(j) {}

public:
    int i, j;
};

class Print
{
private:
    const static string kTag;

public:
    template <typename T, typename U>
    static void Map(const map<T, U>& container, string tag = kTag)
    {
        cout << tag << endl;
        for (auto e : container)
        {
            cout << e.first << " " << e.second << endl;
        }
        cout << endl;
    }

    template <typename T>
    static void Container(const T& container, string tag = kTag)
    {
        cout << tag << endl;
        for (auto e : container)
        {
            cout << e << " ";
        }
        cout << endl;
    }

    template <typename CustomType>
    static void Custom(const vector<CustomType>& container, string tag = kTag)
    {
        cout << tag << endl;
        for (auto e : container)
        {
            e.Print();
        }
        cout << endl;
    }

    template<size_t M, size_t N>
    static void Board(const int board[M][N], string tag = kTag)
    {
        //cout << tag << endl;
        for (int i = 0; i < M; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
        //cout << endl;
    }


    static void Data(const vector<Data>& positions, string tag = kTag)
    {
        cout << tag << endl;
        for (auto p : positions)
        {
            int i = p.i;
            int j = p.j;

            cout << i << " " << j << endl;
        }
        cout << endl;
    }
};
const string Print::kTag = "------------------------------------";


const int N = 9;
const vector<int> base_numbers = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
int board[N][N] = { };


void GetPossibleNumbers(int si, int sj, vector<int>& out)
{
    vector<int> numbers(N * 3);
    for (int i = 0; i < N; ++i)
    {
        int num = board[si][i];
        if (num > 0)
        {
            numbers[i] = num;
        }
    }

    for (int i = 0; i < N; ++i)
    {
        int num = board[i][sj];
        if (num > 0)
        {
            numbers[N + i] = num;
        }
    }

    int start_i = (si / 3) * 3;
    int start_j = (sj / 3) * 3;
    int cnt = 0;

    for (int i = start_i; i < start_i + 3; ++i)
    {
        for (int j = start_j; j < start_j + 3; ++j)
        {
            int num = board[i][j];
            if (num > 0)
            {
                numbers[N * 2 + cnt] = num;
            }
            cnt++;
        }
    }

    sort(begin(numbers), end(numbers));
    auto it = unique(begin(numbers), end(numbers));
    numbers.erase(it, end(numbers));

    set_difference(begin(base_numbers), end(base_numbers), begin(numbers), it, back_inserter(out));

}

bool found = false;
void Sudoku(const vector<Data>& positions, int current)
{
    if (current == positions.size())
    {
        Print::Board<N, N>(board);
        found = true;
        return;
    }

    if (found)return;

    const Data& data = positions[current];

    // make selections
    vector<int> selections;
    GetPossibleNumbers(data.i, data.j, selections);

    for (auto e : selections)
    {
        board[data.i][data.j] = e;
        Sudoku(positions, current + 1);
        board[data.i][data.j] = 0;
    }
}


int main()
{
    vector<Data> positions;
    
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            cin >> board[i][j];
        }
    }

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            if (board[i][j] <= 0)
            {
                Data data(i, j);
                positions.push_back(data);
            }
        }
    }

    Sudoku(positions, 0);
    return 0;
}

/*
testcase 1
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0

answer 1
1 2 3 4 5 6 7 8 9
4 5 6 7 8 9 1 2 3
7 8 9 1 2 3 4 5 6
2 1 4 3 6 5 8 9 7
3 6 5 8 9 7 2 1 4
8 9 7 2 1 4 3 6 5
5 3 1 6 4 2 9 7 8
6 4 2 9 7 8 5 3 1
9 7 8 5 3 1 6 4 2

testcase 2
0 2 0 9 0 5 0 0 0
5 9 0 0 3 0 2 0 0
7 0 0 6 0 2 0 0 5
0 0 9 3 5 0 4 6 0
0 5 4 0 0 0 7 8 0
0 8 3 0 2 7 5 0 0
8 0 0 2 0 9 0 0 4
0 0 5 0 4 0 0 2 6
0 0 0 5 0 3 0 7 0

answer 2
3 2 1 9 7 5 6 4 8
5 9 6 8 3 4 2 1 7
7 4 8 6 1 2 9 3 5
1 7 9 3 5 8 4 6 2
2 5 4 1 9 6 7 8 3
6 8 3 4 2 7 5 9 1
8 1 7 2 6 9 3 5 4
9 3 5 7 4 1 8 2 6
4 6 2 5 8 3 1 7 9
*/


