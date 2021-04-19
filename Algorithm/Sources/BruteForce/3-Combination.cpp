// 조합

// 조합 예제1
// 재귀

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <map>

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
    static void Board(int board[M][N])
    {
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







int main()
{
    const int N = 9;
    int board[N][N] = {1,};


    Print::Board<N, N>(board);

    
    return 0;
}



