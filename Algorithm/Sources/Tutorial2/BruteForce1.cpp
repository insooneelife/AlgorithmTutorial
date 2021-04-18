#include <iostream>
#include <vector>
using namespace std;

const int N = 4;

void Print(const vector<int>& vec)
{
    for (auto e : vec)
    {
        cout << e << " ";
    }
    cout << endl;
}

void Combinations(vector<int>& combs, int selections)
{
    if (selections == 0)
    {
        Print(combs);
        return;
    }

    int start = combs.size() == 0 ? 0 : combs.back() + 1;

    for (int i = start; i < N; ++i)
    {
        combs.push_back(i);
        Combinations(combs, selections - 1);
        combs.pop_back();
    }
}


int main()
{
    vector<int> combs;

    Combinations(combs, 2);

    return 0;
}