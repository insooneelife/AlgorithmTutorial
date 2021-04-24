#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <algorithm>
#include "Print.h"

using namespace std;

struct Data
{
    
    string genre;
    int play;
};

int main()
{
    vector<string> genres{ "temp", "classicc", "pop", "classic2", "classic", "pop", "pop" };
    vector<int> plays{ 800, 500, 600, 150, 800, 2500, 800 };
    
    vector<Data> datas;

    for (int i = 0; i < genres.size(); ++i)
    {
        Data data;
        data.genre = genres[i];
        data.play = plays[i];

        datas.push_back(data);
    }

    sort(begin(datas), end(datas), [](const Data& a, const Data& b)
        {
            if (a.play == b.play)
            {
                return a.genre < b.genre;
            }

            return a.play < b.play;
        });

    for (int i = 0; i < datas.size(); ++i)
    {
        cout << datas[i].genre << " " << datas[i].play << endl;
    }



    return 0;
}

// 정렬 문제 3
// 베스트앨범
// https://programmers.co.kr/learn/courses/30/lessons/42579









// 돈 -> 적성
// 노력 -> 보상

// 회사 -> 목표 x
// 회사 -> 수단

// 목표 (돈, 명성, 세상에 이로운 무언가?, 진정한 개발자)
// "돈"이 목표?

// 연봉을 올려서 부자가 되겠다?
// 어림도 없음....

// 경제공부 필수
// 자본주의 게임 (경제는 규칙) 
// 돈
// 자동으로 수익률이 나오는 시스템 구축
// 1억을 투자해서 오피스텔을 산다. (빚?, 세금?)
// 매달 50만원 수입

// 주식 배당금?

// 창업 (게임 어플, 일반 어플, 웹사이트, 과금 (수익률 보장))

// 유튜브

// 강의 판매


// 바람의나라 
// 메크로 (수지 메크로) + 멀티 (멀티 로그인)
// 계정 20~30개   + 메크로  호박노가다 중2 월 150만원 (2~3개월)
// 충격!
// "메크로 개발자" == 짱
// 테스트 베타 x 
// 동경심   수학 루트 
// 대학교 1학년 C언어
// 리니지 메크로 바람의나라 메크로  (대학교 4학년) 소원을 이룸
// 진정한 개발자가 되기 위해