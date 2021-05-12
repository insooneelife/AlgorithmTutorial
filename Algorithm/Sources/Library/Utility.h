#pragma once

#include "Headers.h"
#include "Print.h"

class Utility
{
public:
    struct Time
    {
        Time() : tm(), milisec(0) {}

        // "08:31", "19:59"
        void ParseHourMinSec(std::string time)
        {
            Parse(time, "%H:%M:%S");
        }

        // "08:31", "19:59"
        void ParseHourMin(std::string time)
        {
            Parse(time, "%H:%M");
        }

        // "55:31", "00:59"
        void ParseMinSec(std::string time)
        {
            Parse(time, "%M:%S");
        }

        // time : "2017.10.30 08:31:05.312"
        // format : "%Y.%m.%d %H:%M:%S.%s"
        void Parse(std::string time, std::string format)
        {
            size_t index = format.find(".%s");

            if (index != std::string::npos)
            {
                size_t rindex = time.rfind(format[index]);
                std::string sub = time.substr(rindex, time.size() - rindex);
                milisec = stof(sub) * 1000;
            }

            std::istringstream ss(time);
            ss >> std::get_time(&tm, format.c_str());
        }

        long long Second() const
        {
            return tm.tm_sec;
        }

        long long Minute() const
        {
            return tm.tm_min;
        }

        long long Hour() const
        {
            return tm.tm_hour;
        }

        long long YearDay() const
        {
            return tm.tm_yday;
        }

        long long MonthDay() const
        {
            return tm.tm_mday;
        }

        long long WeekDay() const
        {
            return tm.tm_wday;
        }

        long long Month() const
        {
            return (long long)tm.tm_mon + (long long)1;
        }

        long long Year() const
        {
            return (long long)tm.tm_year + (long long)1900;
        }

        long long ToKey() const
        {
            long long total = tm.tm_year;
            total *= 12;
            total += tm.tm_mon;
            total *= 32;
            total += tm.tm_mday;
            total *= 24;
            total += tm.tm_hour;
            total *= 60;
            total += tm.tm_min;
            total *= 60;
            total += tm.tm_sec;

            return total;
        }

        void FromKey(long long key)
        {
            tm.tm_sec = key % 60;
            key /= 60;
            tm.tm_min = key % 60;
            key /= 60;
            tm.tm_hour = key % 24;
            key /= 24;
            tm.tm_mday = key % 32;
            key /= 32;
            tm.tm_mon = key % 12;
            key /= 12;
            tm.tm_year = key;
        }

        void Print() const
        {
            std::cout << "Key : " << ToKey() << "\tYear : " << Year() << "\tMonth : " << Month() << "\tMonthDay : " << MonthDay() << "\tHour : " << Hour() << "\tMinute : " << Minute() << "\tSecond : " << Second() << "\tMilisec : " << milisec << std::endl;
        }

    private:
        std::tm tm;
        int milisec;
    };


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


    // is in 2d-array range
    bool InArray2D(int n, int a, int b)
    {
        return  0 <= a && a < n && 0 <= b && b < n;
    }

    // is in 2d-array range
    bool InArray(int n, int a)
    {
        return  0 <= a && a < n;
    }
};
