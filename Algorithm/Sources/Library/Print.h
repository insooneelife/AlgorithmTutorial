#pragma once

#include "Headers.h"


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
        if (tag.size() > 0)
            cout << tag << endl;

        for (auto e : container)
        {
            cout << e << " ";
        }
        cout << endl;
    }
        
    template <typename T>
    static void ContainerInContainer(const T& container_in_vector, std::string tag = kTag)
    {
        using namespace std;
        cout << tag << endl;
        
        for (auto container : container_in_vector)
        {
            Container(container, tag);
        }
        cout << tag << endl;
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

    template <typename T>
    static void Binary(T val, std::string tag = "")
    {
        using namespace std;
        if(tag != "")
            cout << tag << endl;
        cout << "val\t: " << (unsigned long long)val << endl;
        cout << "binary\t: " << bitset<sizeof(T) * 8>(val) << endl << endl;
    }

    template <typename T, typename FormatType>
    static void Binary(T val, std::string tag = "")
    {
        using namespace std;
        if (tag != "")
            cout << tag << endl;
        cout << "val\t: " << (unsigned long long)val << endl;
        cout << "binary\t: " << bitset<sizeof(FormatType) * 8>(val) << endl << endl;
    }

};
const std::string Print::kTag = "------------------------------------";