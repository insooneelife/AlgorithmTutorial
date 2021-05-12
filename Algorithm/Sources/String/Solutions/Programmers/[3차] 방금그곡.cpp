

// [3차] 방금그곡
// https://programmers.co.kr/learn/courses/30/lessons/17684

// 시행착오
// 1. 미리 순환이 포함된 멜로디 문자열을 만들고 시작했으면 훨씬 편하게 작업할 수 있었음
// 2. 문자열 순환 매칭보다는 만들어진 멜로디 문자열에서 find를 사용하는것이 훨씬 편함.
// 3. 답이 없는 경우 None을 리턴

#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <algorithm>
#include <map>
#include <chrono>
#include <sstream>
#include <iomanip>
//#include "Utility.h"

using namespace std;

struct Time
{
    Time() : tm() {}

    // "08:31", "19:59"
    void ParseHourMinSec(string time)
    {
        Parse(time, "%H:%M:%S");
    }

    // "08:31", "19:59"
    void ParseHourMin(string time)
    {
        Parse(time, "%H:%M");
    }

    // "55:31", "00:59"
    void ParseMinSec(string time)
    {
        Parse(time, "%M:%S");
    }

    // time : "2017.10.30 08:31:05"
    // format : "%Y.%m.%d %H:%M:%S"
    void Parse(string time, string format)
    {
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
        cout << "Key : " << ToKey() << "\tYear : " << Year() << "\tMonth : " << Month() << "\tMonthDay : " << MonthDay() << "\tHour : " << Hour() << "\tMinute : " << Minute() << "\tSecond : " << Second() << endl;
    }

private:
    std::tm tm;
};

struct Data
{
    string name;
    string melody;
    int i;
};

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

static char GetLowercase(char c)
{
    return c - 'A' + 'a';
}

string Convert(string str)
{
    for (int i = 0; i < str.size() - 1; ++i)
    {
        if (str[i + 1] == '#')
        {
            str[i] = GetLowercase(str[i]);
        }
    }

    string convert = "";
    for (int i = 0; i < str.size(); ++i)
    {
        if (str[i] != '#')
        {
            convert += str[i];
        }
    }
    return convert;
}

string Melody(const string& part, int length)
{
    string melody = "";

    for (int i = 0; i < length; ++i)
    {
        melody += part[i % part.size()];
    }

    return melody;
}

string solution(string m, vector<string> musicinfos) 
{
    vector<Data> datas;

    m = Convert(m);
    for (int i = 0; i < musicinfos.size(); ++i)
    {
        string musicinfo = musicinfos[i];
        vector<string> split = Split(musicinfo, ',');
        Time start;
        start.ParseHourMin(split[0]);

        Time end;
        end.ParseHourMin(split[1]);

        Data data;
        long long length = (end.ToKey() / 60) - (start.ToKey() / 60);
        data.name = split[2];

        data.melody = Melody(Convert(split[3]), length);
        data.i = i;
        datas.push_back(data);
    }

    vector<Data> answers;
    for (Data data : datas)
    {
        auto n = data.melody.find(m);

        if (n != std::string::npos)
        {
            answers.push_back(data);
        }
    }

    sort(begin(answers), end(answers), [](const Data& a, const Data& b)
        {
            if (a.melody.size() == b.melody.size())
            {
                return a.i < b.i;
            }

            return a.melody.size() > b.melody.size();
        });

    return answers.size() > 0 ? answers[0].name : "(None)";
}

int main()
{        
    string m = "ABCDEFG"; 
    vector<string> musicinfos = { "12:00,12:14,HELLO,CDEFGAB", "13:00,13:05,WORLD,ABCDEF" };

    //string m = "CC#BCC#BCC#BCC#B";
    //vector<string> musicinfos = { "03:00,03:30,FOO,CC#B", "04:00,04:08,BAR,CC#BCC#BCC#B" };

    //string m = "ABC";
    //vector<string> musicinfos = { "12:00,12:14,HELLO,C#DEFGAB", "13:00,13:05,WORLD,ABCDEF" };

    string answer = solution(m, musicinfos);
    cout << answer;

    return 0;
}