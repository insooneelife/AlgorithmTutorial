// 후보키 (완전탐색, Bitmask)
// https://programmers.co.kr/learn/courses/30/lessons/42890



#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <bitset>
#include <cmath>

//#include "Print.h"

using namespace std;

int solution(vector<vector<string>> relation) 
{
    int p = pow(2, relation[0].size());
    vector<bool> candidate_flags(p, false);

    for (int n = 1; n < p; ++n)
    {
        set<vector<string>> table;
        bool candidate = true;

        for (int i = 0; i < relation.size(); ++i)
        {
            bitset<8> bit(n);
            vector<string> selects;

            for (int j = 0; j < relation[i].size(); ++j)
            {
                bool select = bit[j];

                if (select)
                {
                    selects.push_back(relation[i][j]);
                }
            }

            //Print::Container(selects);
            //cout << bit << endl;

            auto ret = table.insert(selects);
            bool success = ret.second;

            // overlap
            if (!success)
            {
                candidate = false;
                break;
            }
        }
        candidate_flags[n] = candidate;
    }

    //Print::Container(candidate_flags);
    
    for (int i = 1; i < p; ++i)
    {
        for (int j = i + 1; j < p; ++j)
        {
            if (candidate_flags[i] && (i & j) == i)
            {
                candidate_flags[j] = false;
            }
        }
    }

    //Print::Container(candidate_flags);

    int answer = 0;
    for (int i = 1; i < p; ++i)
    {
        if (candidate_flags[i])
        {
            answer++;
        }
    }

    return answer;
}

int main()
{
    vector<vector<string>> relation =
    {
        {"100","ryan","music","2"},
        {"200","apeach","math","2"},
        {"300","tube","computer","3"},
        {"400","con","computer","4"},
        {"500","muzi","music","3"},
        {"600","apeach","music","2"}
    };

    int answer = solution(relation);
    cout << answer << endl;


    return 0;
}