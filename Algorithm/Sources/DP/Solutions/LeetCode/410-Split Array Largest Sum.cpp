#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;


class RecursiveSolution
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
            if (j == 0)
            {
                maxs[j] = nums[j];
            }
            else
            {
                maxs[j] = max(maxs[j - 1], nums[j]);
            }
        }

        partial_sum(begin(psum), end(psum), begin(psum));
    }

    int dp(int m, int n)
    {
        if (m > n)
            return -1;

        if (m == 0)
            return cache[m][n] = psum[n];

        if (m == n)
            return cache[m][n] = maxs[n];

        if (cache[m][n] >= 0)
            return cache[m][n];

        int minval = numeric_limits<int>::max();
        for (int i = m - 1; i < n; ++i)
        {
            int val = dp(m - 1, i);
            int sum = rangeSum(i + 1, n);
            minval = min(minval, max(val, sum));
        }

        return cache[m][n] = minval;
    }

    int splitArray(vector<int>& nums, int m)
    {
        init(nums, m);
        return dp(m - 1, nums.size() - 1);
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
    vector<int> input = { 2,3,1,2,4,3 };

    Solution s;
    int ans = s.splitArray(input, 5);

    cout << ans << endl;

    return 0;
}