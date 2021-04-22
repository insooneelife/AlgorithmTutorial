#pragma once

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>

class Utility
{
public:
    // b가 a의 부분집합인지 확인
    template <typename T>
    static bool IsSubset(const std::vector<T>& a, const std::vector<T>& b)
    {
        using namespace std;

        sort(begin(a), end(a));
        sort(begin(b), end(b));
        return includes(begin(a), end(a), begin(b), end(b));
    }

    // b가 a의 진부분집합인지 확인
    template <typename T>
    static bool IsProperSubset(const std::vector<T>& a, const std::vector<T>& b)
    {
        using namespace std;

        sort(begin(a), end(a));
        sort(begin(b), end(b));

        if (a.size() == b.size()) return false;

        return includes(begin(a), end(a), begin(b), end(b));
    }

    // str을 delimiter 단위로 자른다.
    static std::vector<std::string> Split(const std::string& str, char delimiter)
    {
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream token_stream(str);
        while (std::getline(token_stream, token, delimiter))
        {
            tokens.push_back(token);
        }
        return tokens;
    }

    
    // str을 whitespace 단위로 자른다.
    // (whitespace에는 '\t', ' ', '\n' 과 같은 것들이 있다.)
    // ex)
    // "split\ton   \t white\nspace   ." => { "split", "on", "white", "space", "." }
    static std::vector<std::string> Split(const std::string& str)
    {
        using namespace std;;

        vector<string> results;
        istringstream iss(str);
        for (string s; iss >> s;)
        {
            results.push_back(s);
        }
        return results;
    }

    // line에서 모든 word를 제거한다.
    // ex) ("abcppppppabc", "abc") => "pppppp"
    static void RemoveAllWordsFromLine(std::string& line, const std::string& word)
    {
        while (true)
        {
            auto n = line.find(word);
            if (n != std::string::npos)
            {
                line.erase(n, word.length());
            }
            else
            {
                break;
            }
        }
    }

    // -1 => "-1"
    template<typename T>
    static std::string ToString(T num)
    {
        return std::to_string(num);
    }


    // "-1"  => -1, 
    // "001" =>  1, 
    // "000" =>  0
    static int StringToInt(const std::string& str)
    {
        return stoi(str);
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

    template <typename T>
    static void ContainerInContainer(const T& container_in_vector, std::string tag = kTag)
    {
        using namespace std;
        cout << tag << endl;
        for (auto container : container_in_vector)
        {
            Container(container);
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
};
const std::string Print::kTag = "------------------------------------";