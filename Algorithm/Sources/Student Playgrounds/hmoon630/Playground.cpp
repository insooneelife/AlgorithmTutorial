// hmoon630 의 작업공간
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

int main()
{
    string text = "aabbbbccccdkkdddd";

    unordered_map<char, int> counts;

    for (auto c : text)
    {
        counts[c]++;
    }

    for (auto e : counts)
    {
        cout << e.first << " " << e.second << endl;
    }

    return 0;
}
