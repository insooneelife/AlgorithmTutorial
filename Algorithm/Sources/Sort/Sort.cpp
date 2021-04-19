// 정렬


#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct Data
{
    int plays;
    string genres;
};
// data 출력용
void print(const vector<Data>& vec)
{
    for (int i = 0; i < vec.size(); ++i)
    {
        cout << vec[i].genres << " " << vec[i].plays << endl;;
    }
    cout << endl;
}
int main()
{
    vector<string> genres{ "zaa", "abc", "bac" "classicc", "pop" };
    vector<int> plays = { 4,6,7,1,5 };
    vector<Data> vec;
    for (int i = 0; i < genres.size(); ++i)
    {
        string gen = genres[i];
        int play = plays[i];
        Data data;
        data.genres = gen;
        data.plays = play;
        vec.push_back(data);
    }
    print(vec);
    // [캡쳐 영역] (인자 영역) { 정책 알고리즘 }
    Data a;
    Data b;
    sort(begin(vec), end(vec), [](const Data& a, const Data& b)
        {
            return a.plays < b.plays;
        });
    print(vec);
    return 0;
}