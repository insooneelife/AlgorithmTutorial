// 메뉴 리뉴얼
// https://programmers.co.kr/learn/courses/30/lessons/72411

#include "Algorithm.h"
#include "Utility.h"

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>

using namespace std;

void Comb(const string& order, int k, vector<string>& combs)
{
    vector<vector<int>> all_combs;
    Algorithm::CombinationsIterate(order.size(), k, all_combs);

    for (int i = 0; i < all_combs.size(); ++i)
    {
        string comb = "";
        for (auto idx : all_combs[i])
        {
            comb += order[idx];
        }
        combs.push_back(comb);
    }
}

void MaxOrders(const map<string, int>& counts, vector<string>& outs)
{
    int maxval = 0;
    for (auto e : counts)
    {
        if (maxval < e.second)
        {
            maxval = e.second;
        }
    }

    for (auto e : counts)
    {
        if (e.second == maxval && maxval >= 2)
        {
            outs.push_back(e.first);
        }
    }
}

vector<string> solution(vector<string> orders, vector<int> courses)
{
    vector<string> answer;

    for (int i = 0; i < orders.size(); ++i)
    {
        sort(begin(orders[i]), end(orders[i]));
    }

    for (int c = 0; c < courses.size(); ++c)
    {
        map<string, int> counts;
        for (int i = 0; i < orders.size(); ++i)
        {
            vector<string> combs;

            Comb(orders[i], courses[c], combs);

            for (string com : combs)
            {
                counts[com]++;
            }
        }
        MaxOrders(counts, answer);
    }

    sort(begin(answer), end(answer));
    return answer;
}



int main()
{
    // Case 1.
    // answer {"AC", "ACDE", "BCFG", "CDE"}
    {
        vector<string> orders = { "ABCFG", "AC", "CDE", "ACDE", "BCFG", "ACDEH" };
        vector<int> courses = { 2, 3, 4 };

        vector<string> answer = solution(orders, courses);

        Print::Container(answer);
    }


    return 0;
}