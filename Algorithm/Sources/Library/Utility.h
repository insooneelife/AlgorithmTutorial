#pragma once

#include "Headers.h"
#include "Print.h"

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

    // str을 모든 delimiter 단위로 자른다. 
    static void Split(const std::string& str, const std::vector<char>& delimiters, std::vector<std::string>& out)
    {
        return Split(str, delimiters, 0, out);
    }

    // str을 모든 delimiter 단위로 자른다. 
    // delimiter도 배열에 포함시킨다.
    static void SplitIncludeDelimiter(
        const std::string& str, const std::vector<char>& delimiters, std::vector<std::string>& out)
    {
        return SplitIncludeDelimiter(str, delimiters, 0, out);
    }

private:
    static void Split(const std::string& str, const std::vector<char>& delimiters, int i, std::vector<std::string>& out)
    {
        using namespace std;
        if (i >= delimiters.size())
        {
            out.push_back(str);
            return;
        }

        char d = delimiters[i];
        vector<string> v = Split(str, d);

        for (int j = 0; j < v.size(); ++j)
        {
            Split(v[j], delimiters, i + 1, out);
        }
    }


    static void SplitIncludeDelimiter(
        const std::string& str, const std::vector<char>& delimiters, int i, std::vector<std::string>& out)
    {
        using namespace std;
        if (i >= delimiters.size())
        {
            out.push_back(str);
            return;
        }

        char d = delimiters[i];
        vector<string> v = Split(str, d);

        for (int j = 0; j < v.size(); ++j)
        {
            Split(v[j], delimiters, i + 1, out);
            if (j < v.size() - 1)
                out.push_back(string(1, d));
        }
    }
public:

    
    

    // str을 whitespace 단위로 자른다.
    // (whitespace에는 '\t', ' ', '\n' 과 같은 것들이 있다.)
    // ex)
    // "split\ton   \t white\nspace   ." => { "split", "on", "white", "space", "." }
    static std::vector<std::string> SplitWhitespace(const std::string& str)
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

    // 소문자 alphabet이 아닌 문자로 자른다.
    std::vector<std::string> SplitNoneAlphabet(const std::string& str)
    {
        using namespace std;
        vector<string> split;
        std::string::const_iterator from = begin(str);
        std::string::const_iterator to = from;

        while (true)
        {
            to = std::find_if(from, end(str), [](char c)
                {
                    return !('a' <= c && c <= 'z');
                });

            string substr = string(from, to);
            if (substr.size() > 0)
            {
                split.push_back(substr);
            }

            if (to == end(str))
                break;

            from = to + 1;
        }

        return split;
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

    static long long StringToLongLong(const std::string& str)
    {
        return stoll(str);
    }

    // "0000.44324" => 0000.44324
    // "-1.44324"   => -1.44324,
    // "-1.44324f"  => -1.44324,
    static float StringToFloat(const std::string& str)
    {
        return stof(str);
    }

    static void ToLowercase(std::string& str)
    {
        for (char& c : str)
        {
            if (IsUppercase(c))
            {
                c = GetLowercase(c);
            }
        }
    }

    static void ToUppercase(std::string& str)
    {
        for (char& c : str)
        {
            if (IsLowercase(c))
            {
                GetUppercase(c);
            }
        }
    }

    static bool IsLowercase(char c)
    {
        return 'a' <= c && c <= 'z';
    }

    static bool IsUppercase(char c)
    {
        return 'A' <= c && c <= 'Z';
    }

    static char GetLowercase(char c)
    {
        return c - 'A' + 'a';
    }

    static char GetUppercase(char c)
    {
        return c - 'a' + 'A';
    }

    // x, y coordinate -> i, j 2d-array
    template<int N>
    static void Set(int board[N][N], int n, int x, int y, int val)
    {
        board[n - 1 - y][x] = val;
    }

    template<int N>
    static int Get(int board[N][N], int n, int x, int y)
    {
        return board[n - 1 - y][x];
    }


    static bool InArray2D(int rows, int columns, int i, int j)
    {
        return
            0 <= i && i < rows &&
            0 <= j && j < columns;
    }

    // is in 2d-array range
    static bool InArray2D(int n, int a, int b)
    {
        return  0 <= a && a < n && 0 <= b && b < n;
    }

    // is in 2d-array range
    static bool InArray(int n, int a)
    {
        return  0 <= a && a < n;
    }

    static void ReverseStack(std::stack<string>& st)
    {
        using namespace std;
        stack<string> temp;
        while (!st.empty())
        {
            string top = st.top();
            temp.push(top);
            st.pop();
        }
        st = temp;
    }

};
