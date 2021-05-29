
// 큰 수 만들기 (탐욕법)
// https://programmers.co.kr/learn/courses/30/lessons/42883


#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <string>
using namespace std;

string solution(string number, int k)
{
    vector<pair<int, vector<int>>> num_idx(10);
    string answer = "";

    k = number.size() - k;

    for (int i = 0; i < number.size(); ++i)
    {
        int num = number[i] - '0';
        num_idx[num].second.push_back(number.size() - i);
    }
    
    int last = 0;
    while (k > 0)
    {
        bool found = false;
        for (int i = num_idx.size() - 1; i >= 0; --i)
        {
            int val = i;
            int& idx = num_idx[i].first;
            vector<int>& que = num_idx[i].second;

            if (idx < que.size())
            {
                int back = que[idx];
                if (found)
                {
                    while (idx < que.size() && que[idx] > last)
                    {
                        idx++;
                    }
                }
                else if(back >= k)
                {
                    answer += (val + '0');
                    last = back;
                    idx++;
                    k--;
                    found = true;
                }
            }
        }
    }
    
    return answer;
}

int main()
{
    string number = "4177252841";
    int k = 4;

    string ans = solution(number, k);
    cout << ans << endl;

    return 0;
}



#include <fstream>
#include <iostream>
void MakeTestcase()
{
    string number = "";
    for (int i = 0; i < 1000000; ++i)
    {
        number += '1';
    }
    int k = number.size() / 2;

    string ans = solution(number, k);
    cout << number.size() << " " << k << " " << ans.size() << endl;

    // make testcase;
    string filePath = "test.txt";

    // write File
    ofstream writeFile(filePath.data());
    if (writeFile.is_open())
    {
        writeFile << number << endl;
        writeFile << ans << endl;
        writeFile.close();
    }
}