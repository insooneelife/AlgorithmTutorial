// ¿ß¿Â
// https://programmers.co.kr/learn/courses/30/lessons/42578

// solution 1.
#include <string>
#include <vector>
#include <iostream>
#include <map>

using namespace std;

int mem[31][31] = { 0 };

int comb(const vector<int>& mapping, int n, int k)
{
    if (mem[n][k] > 0) return mem[n][k];
    if (k == 0) return mem[n][k] = 1;
    if (n == k) return mem[n][k] = mapping[n] * comb(mapping, n - 1, k - 1);

    return mem[n][k] = mapping[n] * comb(mapping, n - 1, k - 1) + comb(mapping, n - 1, k);
}

int solution(vector<vector<string>> clothes) 
{
    int answer = 0;

    map<string, int> clothmap;
    vector<int> mapping{ 0 };

    for (int i = 0; i < clothes.size(); ++i)
    {
        string value = clothes[i][0];
        string key = clothes[i][1];
        clothmap[key] ++;
    }

    for (auto e : clothmap)
    {
        mapping.push_back(e.second);
    }

    int sum = 0;
    for (int k = 1; k <= clothmap.size(); ++k)
    {
        sum += comb(mapping, clothmap.size(), k);
    }

    return sum;
}


// solution 2.
#include <string>
#include <vector>
#include <iostream>
#include <map>

using namespace std;

int solution(vector<vector<string>> clothes) 
{
    map<string, int> clothmap;

    for (int i = 0; i < clothes.size(); ++i)
    {
        string value = clothes[i][0];
        string key = clothes[i][1];

        clothmap[key]++;
    }

    int sum = 1;
    for (auto e : clothmap)
    {
        sum *= (e.second + 1);
    }

    return sum - 1;
}