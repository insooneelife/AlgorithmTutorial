// 정수 삼각형
// https://programmers.co.kr/learn/courses/30/lessons/43105

#include <string>
#include <vector>
using namespace std;

int solution(vector<vector<int>> tri)
{
    for (int i = tri.size() - 1; i >= 1; --i)
        for (int j = i; j >= 1; --j)
            tri[i - 1][j - 1] += max(tri[i][j], tri[i][j - 1]);

    return tri[0][0];
}

int main()
{
    vector<vector<int>> triangle = { {7} ,{3, 8},{8, 1, 0},{2, 7, 4, 4},{4, 5, 2, 6, 5} };
    cout << solution(triangle);

    return 0;
}