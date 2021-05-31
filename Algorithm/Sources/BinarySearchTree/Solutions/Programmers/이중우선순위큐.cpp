
// 이중우선순위큐 (이진트리)
// https://programmers.co.kr/learn/courses/30/lessons/42628

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
#include <functional>
using namespace std;

vector<int> solution(vector<string> operations) 
{
    multiset<int> S;
    for (string op : operations)
    {
        string command = op.substr(0, 1);
        int val = stoi(op.substr(2, op.size() - 2));

        if (command == "I")
        {
            S.insert(val);
        }
        else if(S.size() > 0)
        {
            multiset<int, int>::iterator it;
            if (val == 1)
            {
                it = S.end();
                --it;
            }
            else
            {
                it = S.begin();
            }
            
            S.erase(it);
        }
    }

    if (S.empty())
    {
        return {0, 0};
    }
    else
    {
        auto it = S.begin();
        auto rit = S.end();
        rit--;

        return { *rit, *it };
    }
}



int main()
{
    vector<string> operations = { "I 7", "I 5", "I -5", "D -1" };
    auto v = solution(operations);
    cout << v[0] << " " << v[1] << endl;


    return 0;
}