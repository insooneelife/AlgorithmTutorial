#pragma once

#include "Headers.h"
#include "Print.h"

template<typename T>
struct Vec
{
    Vec() : x(0), y(0) {}
    Vec(int x, int y) : x(x), y(y) {}

public:
    bool operator==(const Vec& other) const
    {
        return x == other.x && y == other.y;
    }

    bool operator<(const Vec& other) const
    {
        if (x == other.x)
        {
            return y < other.y;
        }

        return x < other.x;
    }

    // for greater
    bool operator>(const Vec& other) const
    {
        if (x == other.x)
            return y > other.y;

        return x > other.x;
    }

    Vec operator+(const Vec& other) const
    {
        return Vec(x + other.x, y + other.y);
    }

    Vec operator-(const Vec& other) const
    {
        return Vec(x - other.x, y - other.y);
    }

    // unary minus
    Vec operator- ()
    {
        return Vec(-x, -y);
    }

public:
    T x;
    T y;
};

struct Time
{
    Time() : tm(), milisec(0) {}

    // "08:31", "19:59"
    void ParseHourMinSecMilisec(std::string time)
    {
        Parse(time, "%H:%M:%S.%s");
    }

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

    // time : "2017.10.30 08:31:05.312",    "2017-10-30 08-31-05-312"
    // format : "%Y.%m.%d %H:%M:%S.%s",     "%Y-%m-%d %H-%M-%S-%s"
    void Parse(std::string time, std::string format)
    {
        size_t index = format.find("%s");

        if (index != std::string::npos)
        {
            size_t rindex = time.rfind(format[index - 1]);
            std::string sub = time.substr(rindex + 1, 3);
            milisec = stof(sub);
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
        total *= 1000;
        total += milisec;

        return total;
    }

    void FromKey(long long key)
    {
        milisec = key % 1000;
        key /= 1000;
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

struct State
{
    int i, j, cnt;
};