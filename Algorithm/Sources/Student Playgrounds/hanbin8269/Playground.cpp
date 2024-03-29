// hanbin8269 의 작업공간

// Stack, Queue
// 프로그래머스 기능개발
// https://hanbin8269.tistory.com/21
// 프로그래머스 다리를 지나는 트럭
// https://hanbin8269.tistory.com/23
// 프로그래머스 프린터
// https://hanbin8269.tistory.com/25
// 프로그래머스 크레인 인형뽑기
// https://hanbin8269.tistory.com/33

// Heap
// 프로그래머스 더 맵게
// https://hanbin8269.tistory.com/28

// DFS
// 프로그래머스 타겟넘버
// https://hanbin8269.tistory.com/30
// [피드백]
// bitmask를 이용해서도 풀어보세요


// Hash
// 프로그래머스 위장
// https://hanbin8269.tistory.com/18
// [피드백]
// 굳 :)

// 프로그래머스 베스트 앨범
// https://hanbin8269.tistory.com/19

// 프로그래머스 전화번호 목록
// https://hanbin8269.tistory.com/26


// Greedy
// 프로그래머스 체육복
// https://hanbin8269.tistory.com/20
// [피드백]
// 1. 차집합을 이용해보세요
// https://www.geeksforgeeks.org/python-set-difference/

// 2. O(NlogN)으로 풀려면 어떻게 해야 할까요?



#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

class Solution 
{
public:
    vector<vector<int>> cache;
    vector<int> psum;
    vector<int> maxs;

    int rangeSum(int from, int to)
    {
        if (from == 0) return psum[to];
        return psum[to] - psum[from - 1];
    }

    void init(const vector<int>& nums, int m)
    {
        psum.resize(nums.size());
        maxs.resize(nums.size());
        cache.resize(m);
        for (int i = 0; i < cache.size(); ++i)
        {
            cache[i].resize(nums.size());
        }

        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < nums.size(); ++j)
            {   
                cache[i][j] = -1;
            }
        }

        for (int j = 0; j < nums.size(); ++j)
        {
            psum[j] = nums[j];
            cache[0][j] = nums[j];

            if (j == 0)
            {
                maxs[j] = nums[j];
            }
            else
            {
                maxs[j] = max(maxs[j - 1], nums[j]);
            }
        }

        for (int i = 0; i < m; ++i)
        {
            cache[i][i] = maxs[i];
        }
        
        partial_sum(begin(psum), end(psum), begin(psum));
        partial_sum(begin(cache[0]), end(cache[0]), begin(cache[0]));
    }

    int splitArray(vector<int>& nums, int m)
    {
        init(nums, m);

        //print();

        for (int i = 1; i < m; ++i)
        {
            for (int j = i + 1; j < nums.size(); ++j)
            {
                int minval = numeric_limits<int>::max();

                for (int k = i; k <= j; ++k)
                {
                    int sum = rangeSum(k, j);
                    int val = cache[i - 1][k - 1];

                    minval = min(minval, max(val, sum));
                }

                cache[i][j] = minval;
            }
        }

        //print();

        return cache[m - 1][nums.size() - 1];
    }

    void print()
    {
        cout << "cache" << endl;
        for (int i = 0; i < cache.size(); ++i)
        {
            for (int j = 0; j < cache[i].size(); ++j)
            {
                cout << cache[i][j] << ", ";
            }
            cout << endl;
        }

        cout << "psum" << endl;

        for (int j = 0; j < cache[0].size(); ++j)
        {
            cout << psum[j] << ", ";
        }
        cout << endl << endl;
    }
};


int main()
{
    vector<int> input = {2,3,1,2,4,3};

    Solution s;
    int ans = s.splitArray(input, 5);

    cout << ans << endl;

    return 0;
}