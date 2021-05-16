
// 삼각 달팽이
// https://programmers.co.kr/learn/courses/30/lessons/68645

#include <string>
#include <vector>
//#include "Print.h"

using namespace std;

enum class Type : int
{
    Down, Right, Up
};

vector<int> solution(int n) 
{
    const int N = n * (n + 1) / 2;
    const vector<Type> types = { Type::Down, Type::Right, Type::Up };
    vector<int> amount(n);
    vector<int> lines(N);
    vector<int> indices(N);
    vector<int> answer(N);

    for (int i = 0; i < n; i++)
    {
        amount[i] = n - i;
    }
    amount[0]--;
    
    int idx = 0;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            lines[idx++] = i;
        }
    }

    int curr = 0;
    idx = 0;
    for (int i = 0; i < amount.size(); ++i)
    {
        int loops = amount[i];
        for (int j = 0; j < loops; ++j)
        {
            Type type = types[i % types.size()];
            int add = 1;

            if (type == Type::Down)
                add = lines[curr];
            else if (type == Type::Up)
                add = -lines[curr];
            
            indices[idx] = curr;
            curr = curr + add;
            idx++;
        }
    }
    indices[idx] = curr;

    for (int i = 0; i < N; ++i)
    {
        answer[indices[i]] = i + 1;
    }

    return answer;
}

int main()
{
    int n = 6;
    vector<int> answer = solution(n);
    //Print::Container(answer);

    return 0;
}