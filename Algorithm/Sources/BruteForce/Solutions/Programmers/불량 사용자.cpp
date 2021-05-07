
// 불량 사용자 (조합 & 순열)
// https://programmers.co.kr/learn/courses/30/lessons/64064

#include <string>
#include <vector>
#include <iostream>
#include <stack>
#include <sstream>
#include <algorithm>
#include "Print.h"

using namespace std;

void Comb(int n, int k, vector<vector<int>>& all_combs, vector<int>& combs)
{
    if (k == 0)
    {
        all_combs.push_back(combs);
        return;
    }

    int start = combs.size() > 0 ? combs.back() + 1 : 0;
    for (int i = start; i < n; ++i)
    {
        combs.push_back(i);
        Comb(n, k - 1, all_combs, combs);
        combs.pop_back();
    }
}

void Comb(int n, int k, vector<vector<int>>& all_combs)
{
    vector<int> combs;
    Comb(n, k, all_combs, combs);
}

bool CompareId(const string& uid, const string& bid)
{
    if (uid.size() != bid.size())
        return false;

    for (int i = 0; i < uid.size(); ++i)
    {
        if (bid[i] == '*')
        {
        }
        else
        {
            if (bid[i] != uid[i])
            {
                return false;
            }
        }
    }
    return true;
}

bool CheckInPermutation(const vector<string>& user_id, const vector<string>& banned_id, const vector<int>& combs)
{
    vector<int> bindex(banned_id.size());
    for (int i = 0; i < bindex.size(); ++i)
        bindex[i] = i;

    do
    {
        bool compare = true;

        for (int i = 0; i < combs.size(); ++i)
        {
            int uid = combs[i];
            int bid = bindex[i];

            if (!CompareId(user_id[uid], banned_id[bid]))
            {
                compare = false;
                break;
            }
        }

        if (compare)
            return true;

    } while (next_permutation(bindex.begin(), bindex.end()));

    return false;
}

int solution(vector<string> user_id, vector<string> banned_id)
{
    vector<vector<int>> all_combs;
    Comb(user_id.size(), banned_id.size(), all_combs);

    int answer = 0;
    for (const vector<int>& combs : all_combs)
    {
        if (CheckInPermutation(user_id, banned_id, combs))
        {
            answer++;
        }
    }

    return answer;
}

int main()
{
    vector<string> user_id = { "frodo", "fradi", "crodo", "abc123", "frodoc" };
    //vector<string> banned_id = { "*rodo", "*rodo", "******" };
    vector<string> banned_id = { "fr*d*", "*rodo", "******", "******" };

    int answer = solution(user_id, banned_id);
    cout << answer;

    return 0;
}