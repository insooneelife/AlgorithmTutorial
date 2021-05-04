
// 실패율 (부분합, 정렬)
// https://programmers.co.kr/learn/courses/30/lessons/42889

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include "Print.h"

using namespace std;

vector<int> solution(int N, vector<int> stages) 
{
    int size = N + 2;
    vector<int> failes(size, 0);
    vector<int> sum_failes(size, 0);
    vector<pair<float, int>> vals;

    for (auto stage : stages)
    {
        failes[stage]++;
    }

    for (int i = 1; i < failes.size(); ++i)
    {
        sum_failes[i] = sum_failes[i - 1] + failes[i];
        int tri_cnt = stages.size() - sum_failes[i - 1];
        float val = (float)failes[i] / (float)tri_cnt;

        if(i < failes.size() - 1)
            vals.push_back(make_pair(-val, i));
    }

    vector<int> answer;
    sort(begin(vals), end(vals));

    for (auto e : vals)
    {
        answer.push_back(e.second);
    }
    return answer;
}



int main()
{
    int N = 5;
    vector<int> stages = {2, 1, 2, 6, 2, 4, 3, 3};
    vector<int> answer = solution(N, stages);

    Print::Container(answer);

    return 0;
}