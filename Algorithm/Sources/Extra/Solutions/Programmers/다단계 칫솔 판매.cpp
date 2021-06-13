
// 다단계 칫솔 판매 (트리)
// https://programmers.co.kr/learn/courses/30/lessons/77486

// 시행착오
// 1. 10%를 계산한 금액이 1 원 미만인 경우에는 이득을 분배하지 않고 자신이 모두 가집니다. <- 이 조건으로 인해,
// 미리 수익금의 합을 구해서 계산하면 안된다.

#include <string>
#include <vector>
#include <algorithm>
#include <map>
//#include "Print.h"
using namespace std;

vector<int> solution(vector<string> enroll, vector<string> referral, vector<string> seller, vector<int> amounts) 
{
    vector<int> parents(enroll.size());
    vector<int> sum(enroll.size());
    map<string, int> indices;

    for (int i = 0; i < enroll.size(); ++i)
    {
        auto it = find(begin(enroll), end(enroll), referral[i]);
        int index = it - begin(enroll);
        parents[i] = index;
        indices[enroll[i]] = i;
    }


    for (int i = 0; i < seller.size(); ++i)
    {
        int node = indices[seller[i]];
        int profit = amounts[i] * 100;
        while (node < enroll.size())
        {
            int other = profit / 10;
            int mine = profit - other;

            if (profit < 10)
            {
                mine = profit;
                sum[node] += mine;
                break;
            }
            else
            {
                sum[node] += mine;
            }

            node = parents[node];
            profit = profit / 10;
        }
    }
    
    return sum;
}


int main()
{
    /*
    vector<string> enroll = { "john", "mary", "edward", "sam", "emily", "jaimie", "tod", "young" };
    vector<string> referral = { "-", "-", "mary", "edward", "mary", "mary", "jaimie", "edward" };
    vector<string> seller = { "young", "john", "tod", "emily", "mary" };
    vector<int> amount = { 12, 4, 2, 5, 10 };
    */

    
    vector<string> enroll = { "john", "mary", "edward", "sam", "emily", "jaimie", "tod", "young" };
    vector<string> referral = { "-", "-", "mary", "edward", "mary", "mary", "jaimie", "edward" };
    vector<string> seller = { "sam", "emily", "jaimie", "edward" };
    vector<int> amount = { 2, 3, 5, 4 };
    


    vector<int> answer = solution(enroll, referral, seller, amount);

    Print::Container(answer);

    return 0;
}
