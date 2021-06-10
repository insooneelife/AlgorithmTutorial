
// [1차] 셔틀버스
// https://programmers.co.kr/learn/courses/30/lessons/17678

#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

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

    static std::string ToString(long long a, long long b, long long c)
    {
        stringstream ss;
        ss << setfill('0') << setw(2) << a << ":" << setw(2) << b << ":" << setw(2) << c;
        return ss.str();
    }

    static std::string ToString(long long a, long long b)
    {
        stringstream ss;
        ss << setfill('0') << setw(2) << a << ":" << setw(2) << b;
        return ss.str();
    }

    void Print() const
    {
        std::cout << "Key : " << ToKey() << "\tYear : " << Year() << "\tMonth : " << Month() << "\tMonthDay : " << MonthDay() << "\tHour : " << Hour() << "\tMinute : " << Minute() << "\tSecond : " << Second() << "\tMilisec : " << milisec << std::endl;
    }

private:
    std::tm tm;
    int milisec;
};

const int MinToMilisec = 1000 * 60;

string solution(int n, int t, int m, vector<string> timetable)
{
    priority_queue<int, vector<int>, greater<int>> times;

    for (int i = 0; i < timetable.size(); i++)
    {
        Time time;
        time.ParseHourMin(timetable[i]);
        times.push(time.ToKey());
    }

    Time start_time;
    start_time.ParseHourMin("09:00");
    int start = start_time.ToKey();
    int now = 0;

    for (int i = 0; i < n; i++)
    {
        now = start + i * t * MinToMilisec;
        int cnt = 0;

        if (i == n - 1)
            m--;

        while (!times.empty() && cnt < m)
        {
            if (times.top() <= now)
            {
                times.pop();
                cnt++;
            }
            else
            {
                break;
            }
        }
    }

    Time result_time;
    int result;
    if (times.empty() || times.top() > now)
    {
        result = now;
    }
    else
    {
        result = times.top() - MinToMilisec;
    }

    result_time.FromKey(result);
    return Time::ToString(result_time.Hour(), result_time.Minute());
}

int main()
{
    /*
    int n = 1;
    int t = 1;
    int m = 5;
    vector<string> timetable = { "08:00", "08:01", "08:02", "08:03" };
    */

    int n = 2;
    int t = 10;
    int m = 2;
    vector<string> timetable = { "09:10", "09:09", "08:00" };

    cout << solution(n, t, m, timetable);

    return 0;
}