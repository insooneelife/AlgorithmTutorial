
// 오픈채팅방 (해시)
// https://programmers.co.kr/learn/courses/30/lessons/42888

// 시행착오
// 1. 빈 log를 answer에 집어넣음

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
//#include "Print.h"

using namespace std;

vector<string> solution(vector<string> record) 
{
    vector<vector<string>> recordv;
    for (const string& s : record)
    {
        vector<string> v;
        istringstream iss(s);
        string temp;

        while (iss >> temp)
        {
            v.push_back(temp);
        }
        recordv.push_back(v);
    }

    map<string, string> id_nick;

    for (const vector<string>& v : recordv)
    {
        string action = v[0];
        string uid = v[1];

        if (action == "Enter")
        {
            string nick = v[2];
            id_nick[uid] = nick;
            //id_nick.insert(make_pair(uid, nick));
        }
        else if (action == "Leave")
        {

        }
        else if (action == "Change")
        {
            string nick = v[2];
            id_nick[uid] = nick;
        }
    }
    
    vector<string> answer;
    for (const vector<string>& v : recordv)
    {
        string action = v[0];
        string uid = v[1];
        string nick = id_nick[uid];
        string log;

        if (action == "Enter")
        {
            log = nick + "님이 들어왔습니다.";
            answer.push_back(log);
        }
        else if (action == "Leave")
        {
            log = nick + "님이 나갔습니다.";
            answer.push_back(log);
        }
    }

    return answer;
}

int main()
{
    vector<string> record =
    {
        "Enter uid1234 Muzi", "Enter uid4567 Prodo","Leave uid1234","Enter uid1234 Prodo","Change uid4567 Ryan"
    };

    vector<string> answer = solution(record);

    for (auto e : answer)
    {
        cout << e << endl;
    }


    return 0;
}