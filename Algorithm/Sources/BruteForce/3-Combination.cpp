// 조합

// 조합 예제1
// 재귀

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <map>
#include <list>

using namespace std; 

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
        cout << tag << endl;
        for (int i = 0; i < M; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
};
const string Print::kTag = "------------------------------------";



const int N = 9;
int board[N][N] = { };
const vector<int> base_numbers = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

void GetPossibleNumbers(int si, int sj, vector<int>& numbers)
{
    for (int i = 0; i < N; ++i)
    {
        int num = board[si][i];
        if (num > 0)
        {
            numbers.push_back(num);
        }
    }

    for (int i = 0; i < N; ++i)
    {
        int num = board[i][sj];
        if (num > 0)
        {
            numbers.push_back(num);
        }
    }

    int start_i = (si / 3) * 3;
    int start_j = (sj / 3) * 3;

    for (int i = start_i; i < start_i + 3; ++i)
    {
        for (int j = start_j; j < start_j + 3; ++j)
        {
            int num = board[i][j];
            if (num > 0)
            {
                numbers.push_back(num);
            }
        }
    }

    sort(begin(numbers), end(numbers));
    auto it = unique(begin(numbers), end(numbers));
    numbers.erase(it, end(numbers));

}

void Sudoku(int line)
{
    if (line == N)
    {
        return;
    }

    for (int i = 0; i < N; ++i)
    {
        if (board[line][i] <= 0)
        {
            vector<int> numbers;
            GetPossibleNumbers(line, i, numbers);

            vector<int> selections;
            set_difference(begin(base_numbers), end(base_numbers), begin(numbers), end(numbers), back_inserter(selections));

            if (selections.size() == 0)
            {
                Sudoku(line + 1);
            }
            else if(selections.size() == 1)
            {

                Sudoku(line + 1);
            }
            else
            {

            }

            
            //SetBoard(n, line, i, -1);
        }
    }
}


int main()
{

    
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            cin >> board[i][j];
        }
    }


    Print::Board<N, N>(board);

    vector<int> numbers;
    GetPossibleNumbers(2, 0, numbers);

    Print::Container(numbers);
    

    return 0;
}



