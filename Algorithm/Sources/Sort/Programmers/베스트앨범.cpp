#include <unordered_map>
#include <iostream>
#include <algorithm>
#include <vector>
#include "Print.h"

using namespace std;

// 장르별 합   기준 정렬 (내림차순)
// 플레이      기준 정렬 (내림차순)
// 고유 번호   기준 정렬 (오름차순)

struct Data
{
    Data(string genres, int gplays, int plays, int index) : genres(genres), gplays(gplays), plays(plays), index(index) {}

    string genres;
    int gplays;
    int plays;
    int index;
};

vector<int> solution(vector<string> genres, vector<int> plays)
{

    unordered_map<string, int> genres_plays;

    vector <Data> vec;

    //  현재 몇개?
    unordered_map<string, int> selection_count;

    // genres_plays를 만듬
    for (int i = 0; i < genres.size(); ++i)
    {
        string g = genres[i];
        int p = plays[i];

        selection_count[g] = 0;

        auto it = genres_plays.find(g);

        // 찾음
        if (it != end(genres_plays))
        {
            it->second = it->second + p;
        }
        // 못찾음
        else
        {
            genres_plays.insert(make_pair(g, p));
        }
    }

    for (int i = 0; i < genres.size(); ++i)
    {
        string g = genres[i];
        int p = plays[i];
        int gplays = genres_plays[g];
        int index = i;

        vec.push_back(Data(g, gplays, p, index));
    }

    sort(begin(vec), end(vec), [](const Data& a, const Data& b)
        {
            if (a.gplays == b.gplays)
            {
                if (a.plays == b.plays)
                {
                    return a.index < b.index;
                }

                return a.plays > b.plays;
            }

            return a.gplays > b.gplays;
        });

    vector<int> answer;
    for (Data d : vec)
    {
        int count = selection_count[d.genres];

        if (count < 2)
        {
            // select
            answer.push_back(d.index);
            selection_count[d.genres] = count + 1;
        }
    }

    return answer;
}

int main()
{
    vector<string> genres = { "classic", "pop", "classic", "classic", "pop" };
    vector<int> plays = { 500, 600, 150, 800, 2500 };

    vector<int> answer = solution(genres, plays);

    Print::Container(answer);

    return 0;
}
