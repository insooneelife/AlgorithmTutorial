
// 매칭 점수
// https://programmers.co.kr/learn/courses/30/lessons/42893


// 시행착오
// 1. "/>" 문자열로 탐색 시, 앞에 공백이 있는 경우가 있으므로 "\"" 문자열로 탐색함
// int to = page.find("/>", from); (오류)
// int to = page.find("\"", from + 1) + 1; (수정)

// 2. 문자열 탐색 위치 버그 
// int end = body.find(">"); (오류) 
// int end = body.find(">", start); (수정)



#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <map>
#include <algorithm>

//#include "Print.h"

using namespace std;

void ChangeCapital(string& str)
{
    for (char& c : str)
    {
        if ('A' <= c && c <= 'Z')
        {
            c = c - 'A' + 'a';
        }
    }
}

std::vector<std::string> SplitWhitespace(const std::string& str)
{
    using namespace std;;

    vector<string> results;
    istringstream iss(str);
    for (string s; iss >> s;)
    {
        results.push_back(s);
    }
    return results;
}

std::vector<std::string> SplitNoneAlphabet(const string& str)
{
    vector<string> split;
    std::string::const_iterator from = begin(str);
    std::string::const_iterator to = from;

    while (true)
    {
        to = std::find_if(from, end(str), [](char c)
            {
                return !('a' <= c && c <= 'z');
            });

        string substr = string(from, to);
        if (substr.size() > 0)
        {
            split.push_back(substr);
        }

        if (to == end(str))
            break;

        from = to + 1;
    }

    return split;
}

string FindUrl(const string& page)
{
    static const string kProp = "<meta property=\"og:url\" content=";

    int from = page.find(kProp) + kProp.size();
    int to = page.find("\"", from + 1) + 1;
    int size = to - from;

    string url = page.substr(from, size);
    return url;
}

string FindBody(const string& page)
{
    static const string kStartBody = "<body>";
    static const string kEndBody = "</body>";
    int start_idx = page.find(kStartBody) + kStartBody.size();
    int end_idx = page.find(kEndBody, start_idx);
    int size = end_idx - start_idx;

    string body = page.substr(start_idx, size);
    return body;
}

vector<string> FindLinks(const string& page, string& body)
{
    static const string kStartLink = "<a href=";
    static const string kEndLink = "</a>";
    vector<string> links;
    body = FindBody(page);

    while (true)
    {
        int start_ref = body.find(kStartLink);
        if (start_ref == std::string::npos)
            break;

        int start = start_ref + kStartLink.size();
        int end = body.find(">", start);
        int size = end - start;

        string link = body.substr(start, size);
        links.push_back(link);

        // remove
        int ref_end = body.find(kEndLink) + kEndLink.size();
        int ref_size = ref_end - start_ref;
        string ref = body.substr(start_ref, ref_size);

        auto n = body.find(ref);
        if (n != std::string::npos)
        {
            body.erase(n, ref.length());
        }
    }

    return links;
}

vector<string> FindWords(const string& page, const string& modified_body)
{
    vector<string> v = SplitWhitespace(modified_body);
    vector<string> words;

    for (string& str : v)
    {
        ChangeCapital(str);
        vector<string> split = SplitNoneAlphabet(str);

        words.insert(end(words), begin(split), end(split));
    }

    return words;
}

struct Data
{
    Data(const string& url, const vector<string>& links, const vector<string>& words, int index, const string& word)
        :
        url(url), links(links), words(words), index(index), score(0), link_score(0)
    {
        for (const string& w : words)
        {
            if (w == word)
            {
                score++;
            }
        }
    }

    float MatchingScore() const { return (float)score + link_score; }
    float PartLinkScore() const { return (float)score / (float)links.size(); }

    void Print() const 
    {
        cout << url << endl;
        cout << "score : " << score << "  link count : " << links.size() << "  partlink score : " << PartLinkScore() << "  link_score : " << link_score << "  matching score : " << MatchingScore() << endl;
        
        for (auto link : links)
        {
            cout << link << endl;
        }
        cout << endl;
        for (auto word : words)
        {
            cout << word << endl;
        }
        cout << endl;
    }

    string url;
    vector<string> links;
    vector<string> words;

    int index;
    int score;
    float link_score;
};

int solution(string word, vector<string> pages)
{
    map<string, Data> datamap;

    ChangeCapital(word);
    for (int i = 0; i < pages.size(); ++i)
    {
        string page = pages[i];
        string url = FindUrl(page);
        string modified_body;
        vector<string> links = FindLinks(page, modified_body);
        vector<string> words = FindWords(page, modified_body);

        Data data(url, links, words, i, word);
        datamap.insert(make_pair(url, data));
    }

    for (pair<const string, Data>& e : datamap)
    {
        Data& data = e.second;
        for (const string& link : data.links)
        {
            auto it = datamap.find(link);
            if (it != end(datamap))
            {
                it->second.link_score += data.PartLinkScore();
            }
        }
    }

    vector<Data> vec;
    for (auto d : datamap)
    {
        //d.second.Print();
        vec.push_back(d.second);
    }

    sort(begin(vec), end(vec), [](const Data& a, const Data& b)
        {
            if (a.MatchingScore() == b.MatchingScore())
            {
                return a.index < b.index;
            }

            return a.MatchingScore() > b.MatchingScore();
        });

    return vec[0].index;
}

int main()
{
    
    string word = "blind";
    vector<string> pages = { 
        "<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://a.com\"/>\n</head>  \n<body>\nBlind Lorem Blind ipsum dolor Blind test sit amet, consectetur adipiscing elit. \n<a href=\"https://b.com\"> Link to b </a>\n</body>\n</html>",
        "<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://b.com\"/>\n</head>  \n<body>\nSuspendisse potenti. Vivamus venenatis tellus non turpis bibendum, \n<a href=\"https://a.com\"> Link to a </a>\nblind sed congue urna varius. Suspendisse feugiat nisl ligula, quis malesuada felis hendrerit ut.\n<a href=\"https://c.com\"> Link to c </a>\n</body>\n</html>", 
        "<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://c.com\"/>\n</head>  \n<body>\nUt condimentum urna at felis sodales rutrum. Sed dapibus cursus diam, non interdum nulla tempor nec. Phasellus rutrum enim at orci consectetu blind\n<a href=\"https://a.com\"> Link to a </a>\n</body>\n</html>" };
    

    /*
    string word = "Muzi";
    vector<string> pages = { 
        "<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://careers.kakao.com/interview/list\"/>\n</head>  \n<body>\n<a href=\"https://programmers.co.kr/learn/courses/4673\"></a>#!MuziMuzi!)jayg07con&&\n\n</body>\n</html>", 
        "<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://www.kakaocorp.com\"/>\n</head>  \n<body>\ncon%\tmuzI92apeach&2<a href=\"https://hashcode.co.kr/tos\"></a>\n\n\t^\n</body>\n</html>" };
    */
    

    int answer = solution(word, pages);
    cout << answer;

    return 0;
}