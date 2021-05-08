// 광고 삽입 (구간합)
// https://programmers.co.kr/learn/courses/30/lessons/72414

// 구간중첩값의 표현을 위해 구간 시작지점을 1, 구간 끝지점을 -1로 체크한다.
// 중첩값[i] = 중첩값[i] + 중첩값[i - 1]을 통해 i~i+1 구간의 중첩값을 만든다. (스위핑)
// 다시 이 중첩값 배열을 이용해 누적값을 만든다.
// 누적값[i] = 누적값[i] + 누적값[i - 1]

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

const int MAX = 360000;
long long psum[MAX] = {};

std::vector<std::string> split(const std::string& s, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream token_stream(s);
    while (std::getline(token_stream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

int string_to_sec(const string& time)
{
    vector<string> times = split(time, ':');
    int hours = stoi(times[0]);
    int minutes = stoi(times[1]);
    int seconds = stoi(times[2]);

    return hours * 3600 + minutes * 60 + seconds;
}

void range_time_to_sec(const string& range_time, int& from, int& to)
{
    vector<string> times = split(range_time, '-');

    from = string_to_sec(times[0]);
    to = string_to_sec(times[1]);
}

string time_format(int time)
{
    if (time < 10)
    {
        return "0" + std::to_string(time);
    }
    else
    {
        return std::to_string(time);
    }
}

string sec_to_string(int sec)
{
    int seconds = sec % 60;
    int minutes = (sec / 60) % 60;
    int hours = (sec / 3600);

    return time_format(hours) + ":" + time_format(minutes) + ":" + time_format(seconds);
}

string solution(string play_time, string adv_time, vector<string> logs)
{
    int play_time_sec = string_to_sec(play_time);
    int adv_time_sec = string_to_sec(adv_time);

    for (int i = 0; i < logs.size(); ++i)
    {
        int from = 0;
        int to = 0;

        range_time_to_sec(logs[i], from, to);
        psum[from] += 1;
        psum[to] += -1;
    }

    for (int i = 1; i < play_time_sec; ++i)
    {
        psum[i] += psum[i - 1];
    }

    for (int i = 1; i < play_time_sec; ++i)
    {
        psum[i] += psum[i - 1];
    }

    long long max_val = -1;
    int max_start_time = 0;
    for (int i = adv_time_sec - 1; i < play_time_sec; ++i)
    {
        long long val;
        if (i >= adv_time_sec)
        {
            val = psum[i] - psum[i - adv_time_sec];
        }
        else
        {
            val = psum[i];
        }


        if (max_val < val)
        {
            max_val = val;
            max_start_time = i - adv_time_sec + 1;
        }
    }

    return sec_to_string(max_start_time);
}