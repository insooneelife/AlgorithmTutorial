// 베스트앨범 (정렬 + 해시)
// https://programmers.co.kr/learn/courses/30/lessons/42579

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
//#include "Print.h"
using namespace std;

struct Data
{
    Data(string genre, int gplays, int plays, int index)
        :
        genre(genre), gplays(gplays), plays(plays), index(index)
    {}

public:
    string genre;
    int gplays;
    int plays;
    int index;
};


vector<int> solution(vector<string> genres, vector<int> plays)
{
    unordered_map<string, int> genre_plays;
    unordered_map<string, int> selected_counts;

    vector<Data> vec;

    for (int i = 0; i < genres.size(); ++i)
    {
        string g = genres[i];
        int p = plays[i];

        genre_plays[g] += p;
        selected_counts[g] = 0;
    }

    for (int i = 0; i < genres.size(); ++i)
    {
        string g = genres[i];
        int p = plays[i];
        int gplays = genre_plays[g];
        vec.push_back(Data(g, gplays, p, i));
    }

    sort(begin(vec), end(vec), [](const Data& a, const Data& b)
        {
            if (a.gplays == b.gplays)
            {
                if (a.plays == b.plays)
                {
                    return a.index < a.index;
                }

                return a.plays > b.plays;
            }

            return a.gplays > b.gplays;
        });

    vector<int> answer;

    for (Data d : vec)
    {

        if (selected_counts[d.genre] < 2)
        {
            answer.push_back(d.index);
            selected_counts[d.genre] ++;
        }
    }


    return answer;
}

int main()
{
    vector<string> genres = { "classic", "pop", "classic", "classic", "pop" };
    vector<int> plays = { 500, 600, 150, 800, 2500 };

    vector<int> answer = solution(genres, plays);
    //Print::Container(answer);

    return 0;
}