// 베스트앨범 (정렬 + 해시)
// https://programmers.co.kr/learn/courses/30/lessons/42579

#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <algorithm>

using namespace std;

struct Data
{
    int genre_play;
    int play;
    int i;

    Data() : genre_play(0), play(0), i(0) {}

    Data(int genre_play, int play, int i) : genre_play(genre_play), play(play), i(i) {}
};

void print(const vector<int>& v)
{
    for (auto e : v)
    {
        cout << e << " ";
    }
    cout << endl;
}

void print(const vector<Data>& v)
{
    for (auto e : v)
    {
        cout << e.genre_play << " " << e.play << " " << e.i << endl;;
    }
    cout << endl;
}

vector<int> solution(vector<string> genres, vector<int> plays)
{
    map<string, int> genre_plays;
    map<int, int> selected_counts;
    vector<Data> datas(genres.size());

    for (int i = 0; i < genres.size(); ++i)
    {
        genre_plays[genres[i]] += plays[i];
    }

    for (int i = 0; i < genres.size(); ++i)
    {
        int genre_play = genre_plays[genres[i]];
        int play = plays[i];

        selected_counts[genre_play] = 0;

        Data data(genre_play, play, i);
        datas[i] = data;
    }

    sort(begin(datas), end(datas),
        [](const Data& a, const Data& b)
        {
            if (a.genre_play == b.genre_play)
            {
                if (a.play == b.play)
                {
                    return a.i < b.i;
                }

                return a.play > b.play;
            }

            return a.genre_play > b.genre_play;
        });

    vector<int> answer;

    // select
    for (int i = 0; i < datas.size(); ++i)
    {
        int genre_play = datas[i].genre_play;
        int count = selected_counts[genre_play];

        if (count < 2)
        {
            selected_counts[genre_play] ++;
            answer.push_back(datas[i].i);
        }
    }

    return answer;
}