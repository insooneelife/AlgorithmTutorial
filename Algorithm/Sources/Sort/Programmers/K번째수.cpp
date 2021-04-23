// K번째수
// https://programmers.co.kr/learn/courses/30/lessons/42748


#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
 
void Print(const vector<int>& v, string tag = "----------------------------")
{
    cout << tag << endl;
    for (auto e : v)
    {
        cout << e << " ";
    }
    cout << endl;
}

vector<int> solution(vector<int> arr, vector<vector<int>> commands)
{
    vector<int> answer;
    for (int i = 0; i < commands.size(); ++i)
    {
        int from = commands[i][0];
        int to = commands[i][1];
        int k = commands[i][2];

        vector<int> vec(begin(arr) + from - 1, begin(arr) + to);
        sort(begin(vec), end(vec));
        //Print(vec);

        answer.push_back(vec[k - 1]);
    }

    return answer;
}