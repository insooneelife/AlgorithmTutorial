// [1차] 추석 트래픽
// https://programmers.co.kr/learn/courses/30/lessons/17676

// 시행착오
// 1. counts 배열이 0인 상황
// 2. 구간을 [start, start + 1000) 외에도, [start - 1000, start) 로도 테스트해야한다.
// 3. overlap 조건 누락, 하나의 선분이 다른 선분 내부에 있는 경우
// 4. ranges 배열에 값이 잘못 들어가 있었음

// 더 좋은 방법
// https://softworking.tistory.com/379

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <algorithm>
#include <map>

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

    void Print() const
    {
        std::cout << "Key : " << ToKey() << "\tYear : " << Year() << "\tMonth : " << Month() << "\tMonthDay : " << MonthDay() << "\tHour : " << Hour() << "\tMinute : " << Minute() << "\tSecond : " << Second() << "\tMilisec : " << milisec << std::endl;
    }

private:
    std::tm tm;
    int milisec;
};

struct Data
{
    Data(long long start, long long end) : start(start), end(end) {}
    long long start;
    long long end;

    bool Overlap(const Data& other) const
    {
        return (start <= other.start && other.start <= end) ||
            (start <= other.end && other.end <= end) ||
            (other.start <= start && end <= other.end);
    }

    void Print() const
    {
        cout << "(" << start << ", " << end << ")  ";
    }
};

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

int solution(vector<string> lines)
{
    vector<Data> timestamps;

    for (string line : lines)
    {
        auto v = SplitWhitespace(line);

        Time time;
        time.ParseHourMinSecMilisec(v[1]);

        int milisec = stof(v[2]) * 1000;
        long long start = time.ToKey() - (long long)milisec + 1LL;
        long long end = time.ToKey();

        timestamps.push_back(Data(start, end));
    }

    vector<int> counts;
    sort(begin(timestamps), end(timestamps), [](Data a, Data b) { return a.start < b.start; });


    for (Data target : timestamps)
    {
        vector<Data> ranges =
        {
            Data(target.start, target.start + 999),
            Data(target.end, target.end + 999),
            Data(target.start - 999, target.start),
            Data(target.end - 999, target.end)
        };

        for (Data range : ranges)
        {
            int cnt = 0;

            for (Data time : timestamps)
            {
                if (time.Overlap(range))
                {
                    cnt++;
                }
            }

            counts.push_back(cnt);
        }
    }

    int max = *max_element(begin(counts), end(counts));

    return max;
}


int main()
{
    /*
    vector<string> lines =
    {
        "2016-09-15 01:00:04.001 2.0s",
        "2016-09-15 01:00:07.000 2s",
    };

    vector<string> lines =
    {
        "2016-09-15 01:00:04.002 2.0s",
        "2016-09-15 01:00:07.000 2s"
    };
    */


    vector<string> lines =
    {
        "2016-09-15 20:59:57.421 0.351s",
        "2016-09-15 20:59:58.233 1.181s",
        "2016-09-15 20:59:58.299 0.8s",
        "2016-09-15 20:59:58.688 1.041s",
        "2016-09-15 20:59:59.591 1.412s",
        "2016-09-15 21:00:00.464 1.466s",
        "2016-09-15 21:00:00.741 1.581s",
        "2016-09-15 21:00:00.748 2.31s",
        "2016-09-15 21:00:00.966 0.381s",
        "2016-09-15 21:00:02.066 2.62s"
    };


    int answer = solution(lines);
    cout << answer;



    return 0;
}





