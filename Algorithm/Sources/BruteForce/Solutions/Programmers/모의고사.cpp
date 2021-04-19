#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
const vector<vector<int>> all_selects = 
{ 
    { 1, 2, 3, 4, 5 }, 
    { 2, 1, 2, 3, 2, 4, 2, 5 }, 
    { 3, 3, 1, 1, 2, 2, 4, 4, 5, 5 } 
};

void Print(const vector<int>& v)
{
    for (auto e : v)
    {
        cout << e << " ";
    }
    cout << endl;
}

vector<int> solution(vector<int> answers) 
{
    vector<int> counts;
    int number = 1;

    for (const vector<int>& selects : all_selects)
    {
        int cnt = 0;
        // n번 수포자
        for (int i = 0; i < answers.size(); ++i)
        {
            int answer = answers[i];
            int select = selects[i % selects.size()];

            if (answer == select)
            {
                cnt++;
            }
        }

        counts.push_back(cnt);
        number++;
    }

    int max_val = *max_element(begin(counts), end(counts));
    vector<int> answer;

    for (int i = 0; i < counts.size(); ++i)
    {
        if (counts[i] == max_val)
        {
            answer.push_back(i + 1);
        }
    }

    return answer;
}


int main()
{
    vector<int> answers = { 1, 3, 2, 4, 2 };
    //vector<int> answers = { 1, 2, 3, 4, 5 };
    vector<int> sol = solution(answers);

    Print(sol);


    return 0;
}
