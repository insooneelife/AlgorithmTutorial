// Ä«Æê (Brute Force)
// https://programmers.co.kr/learn/courses/30/lessons/42842

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <map>

using namespace std; 

class Print
{
private:
    const static string kTag;

public:
    template <typename T, typename U>
    static void Map(const map<T, U>& container, string tag = kTag)
    {
        cout << tag << endl;
        for (auto e : container)
        {
            cout << e.first << " " << e.second << endl;
        }
        cout << endl;
    }

    template <typename T>
    static void Container(const T& container, string tag = kTag)
    {
        cout << tag << endl;
        for (auto e : container)
        {
            cout << e << " ";
        }
        cout << endl;
    }

    template <typename CustomType>
    static void Custom(const vector<CustomType>& container, string tag = kTag)
    {
        cout << tag << endl;
        for (auto e : container)
        {
            e.Print();
        }
        cout << endl;
    }
};
const string Print::kTag = "------------------------------------";



vector<int> solution(int brown, int yellow) 
{
    vector<int> answer;

    for (int x = 1; x <= brown; ++x)
    {
        if (2 * (brown + yellow) == x * (brown - 2 * x + 4))
        {
            int y = (brown - 2 * x + 4) / 2;
            if (y > 0)
            {
                if (x >= y)
                {
                    answer.push_back(x);
                    answer.push_back(y);
                }
            }
        }
    }

    return answer;
}



int main()
{
    int brown = 10, yellow = 2;
    //int brown = 8, yellow = 1;
    //int brown = 24, yellow = 24;

    vector<int> answer = solution(brown, yellow);

    //Print::Container(answer);
    
    return 0;
}



