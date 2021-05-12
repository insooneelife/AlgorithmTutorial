
// [1차] 캐시
// https://programmers.co.kr/learn/courses/30/lessons/17680

// 시행착오
// 1. 대소문자 구분하지 않는 예외처리
// 2. Cache 중복 이슈
// 3. Cache 에서 참조가 된 경우 참조시간 정보 갱신

#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

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


int solution(int cacheSize, vector<string> cities) 
{
    // 데이터, 참조시간
    map<string, int> cache;
    int answer = 0;
    for (int i = 0; i < cities.size(); ++i)
    {
        ToLowercase(cities[i]);

        if (cache.find(cities[i]) != end(cache))
        {
            answer += 1;
        }
        else
        {
            answer += 5;
        }

        cache[cities[i]] = i;

        if (cache.size() > cacheSize)
        {
            int min_index = numeric_limits<int>::max();
            string min_city;
            for (auto e : cache)
            {
                if (min_index > e.second)
                {
                    min_index = e.second;
                    min_city = e.first;
                }
            }
            cache.erase(min_city);
        }
    }

    return answer;
}

int main()
{
    //int cacheSize = 3;
    //vector<string> cities = { "Jeju", "Pangyo", "Seoul", "NewYork", "LA", "Jeju", "Pangyo", "Seoul", "NewYork", "LA" };

    //int cacheSize = 3;
    //vector<string> cities = { "Jeju", "Pangyo", "Seoul", "Jeju", "Pangyo", "Seoul", "Jeju", "Pangyo", "Seoul" };

    //int cacheSize = 2;
    //vector<string> cities = { "Jeju", "Pangyo", "Seoul", "NewYork", "LA", "SanFrancisco", "Seoul", "Rome", "Paris", "Jeju", "NewYork", "Rome" };

    //int cacheSize = 5;
    //vector<string> cities = { "Jeju", "Pangyo", "Seoul", "NewYork", "LA", "SanFrancisco", "Seoul", "Rome", "Paris", "Jeju", "NewYork", "Rome" };

    //int cacheSize = 2;
    //vector<string> cities = { "Jeju", "Pangyo", "NewYork", "newyork" };

    int cacheSize = 0;
    vector<string> cities = { "Jeju", "Pangyo", "Seoul", "NewYork", "LA" };


    cout << solution(cacheSize, cities);

    return 0;
}