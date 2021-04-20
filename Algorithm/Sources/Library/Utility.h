#pragma once

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <algorithm>

class Utility
{
    // b가 a의 부분집합인지 확인
    template <typename T>
    bool IsSubset(const std::vector<T>& a, const std::vector<T>& b)
    {
        using namespace std;

        sort(begin(a), end(a));
        sort(begin(b), end(b));
        return includes(begin(a), end(a), begin(b), end(b));
    }

    // b가 a의 진부분집합인지 확인
    template <typename T>
    bool IsProperSubset(const std::vector<T>& a, const std::vector<T>& b)
    {
        using namespace std;

        sort(begin(a), end(a));
        sort(begin(b), end(b));

        if (a.size() == b.size()) return false;

        return includes(begin(a), end(a), begin(b), end(b));
    }
};

class Print
{

private:
    const static std::string kTag;

public:
    template <typename T, typename U>
    static void Map(const std::map<T, U>& container, std::string tag = kTag)
    {
        using namespace std;
        cout << tag << endl;
        for (auto e : container)
        {
            cout << e.first << " " << e.second << endl;
        }
        cout << endl;
    }

    template <typename T>
    static void Container(const T& container, std::string tag = kTag)
    {
        using namespace std;
        cout << tag << endl;
        for (auto e : container)
        {
            cout << e << " ";
        }
        cout << endl;
    }

    template <typename CustomType>
    static void Custom(const std::vector<CustomType>& container, std::string tag = kTag)
    {
        using namespace std;
        cout << tag << endl;
        for (auto e : container)
        {
            e.Print();
        }
        cout << endl;
    }

    template<size_t M, size_t N>
    static void Board(const int board[M][N])
    {
        using namespace std;
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
const std::string Print::kTag = "------------------------------------";