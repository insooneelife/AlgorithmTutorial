
// 쿠키 구입 (탐욕법)
// https://programmers.co.kr/learn/courses/30/lessons/49995

#include <string>
#include <vector>
#include <iostream>
using namespace std;
using ll = long long;

int solution(vector<int> cookie) 
{
    const int N = cookie.size();
    ll maxsum = 0;

    for (int i = 0; i < cookie.size() - 1; ++i)
    {
        int left = i;
        int right = i + 1;

        ll leftsum = cookie[left];
        ll rightsum = cookie[right];

        while (true)
        {
            if (leftsum == rightsum)
            {
                maxsum = max(maxsum, leftsum);
            }

            if (leftsum < rightsum)
            {
                if (left - 1 < 0) break;
                left--;
                leftsum += cookie[left];
            }
            else 
            {
                if (right + 1 >= N) break;
                right++;
                rightsum += cookie[right];
            }
        }
    }
    return maxsum;
}

int main() 
{
    //vector<int> cookie = { 1, 2, 4, 5 };
    vector<int> cookie = { 1, 1, 2, 3 };
    cout << solution(cookie) << endl;

    return 0;
}
