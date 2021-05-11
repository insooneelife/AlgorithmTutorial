// 메뉴 리뉴얼 (조합)
// https://programmers.co.kr/learn/courses/30/lessons/72411

// 시행착오
// 1. cnt < 2인 케이스 제거를 놓침

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include "Print.h"

using namespace std;

class Combinations
{
public:
    Combinations(const int N, const int K) : N(N), K(K)
    {
        Make();
    }

    void Make()
    {
        Make(K);
    }

private:
    void Make(int k)
    {
        using namespace std;

        if (k == 0)
        {
            all_combs.push_back(combs);
            return;
        }

        int start = combs.size() > 0 ? combs.back() + 1 : 0;
        for (int i = start; i < N; ++i)
        {
            combs.push_back(i);
            Make(k - 1);
            combs.pop_back();
        }
    }

public:
    std::vector<std::vector<int>> all_combs;

private:
    const int N;
    const int K;
    std::vector<int> combs;
};

vector<string> solution(vector<string> orders, vector<int> courses)
{
    vector<string> answer;
    vector<char> all;

    // make universal set
    for (auto order : orders)
    {
        for (char o : order)
        {
            all.push_back(o);
        }
    }
    // remove overlap
    sort(begin(all), end(all));
    auto it = unique(begin(all), end(all));
    all.erase(it, end(all));

    //Print::Container(all);

    for (int i = 0; i < courses.size(); ++i)
    {
        int k = courses[i];
        Combinations combination(all.size(), k);
        vector<pair<int, string>> save;

        for (const vector<int>& v : combination.all_combs)
        {
            string combs;
            for (int index : v)
            {
                char c = all[index];
                combs.push_back(c);
            }

            // check include
            sort(begin(combs), end(combs));
            int cnt = 0;

            for (string order : orders)
            {
                sort(begin(order), end(order));
                if (includes(begin(order), end(order), begin(combs), end(combs)))
                {
                    cnt++;
                }
            }

            if (cnt >= 2)
                save.push_back(make_pair(cnt, combs));
        }

        // make answer
        if (save.size() > 0)
        {
            sort(begin(save), end(save), greater<pair<int, string>>());

            int cnt = save[0].first;
            for (auto e : save)
            {
                if (cnt != e.first)
                    break;

                string combs = e.second;
                answer.push_back(combs);
            }
        }

    }
    sort(begin(answer), end(answer));
    return answer;
}

int main()
{
    //vector<string> orders = { "ABCFG", "AC", "CDE", "ACDE", "BCFG", "ACDEH" };
    //vector<int> courses = { 2,3,4 };

    vector<string> orders = { "ABCDE", "AB", "CD", "ADE", "XYZ", "XYZ", "ACD" };
    vector<int> courses = { 2, 3, 5 };

    vector<string> answer = solution(orders, courses);

    Print::Container(answer);

    return 0;
}