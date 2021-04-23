// 매출 하락 최소화 (DP)
// https://programmers.co.kr/learn/courses/30/lessons/72416

#include <string>
#include <vector>
#include <iostream>
#include <bitset>

using namespace std;

long long D[300001][2] = {};

void print(const vector<vector<int>>& tree)
{
    for (int i = 0; i < tree.size(); ++i)
    {
        cout << "childs of : " << i << endl;
        for (int j = 0; j < tree[i].size(); ++j)
        {
            cout << tree[i][j] << " ";
        }
        cout << endl << endl;
    }
}

long long dy(const vector<int>& sales, const vector<vector<int>>& tree, int n, bool participate)
{
    vector<int> childs = tree[n];

    if (childs.size() == 0)
        return participate ? D[n][participate] = sales[n] : D[n][participate] = 0;

    if (D[n][participate] > 0)
        return D[n][participate];

    long long sum = 0;
    if (participate)
    {
        for (int i = 0; i < childs.size(); ++i)
        {
            sum += min(dy(sales, tree, childs[i], true), dy(sales, tree, childs[i], false));
        }

        return D[n][participate] = sales[n] + sum;
    }
    else
    {
        long long min_sum = numeric_limits<int>::max();
        for (int c = 0; c < childs.size(); ++c)
        {
            sum = dy(sales, tree, childs[c], true);
            for (int i = 0; i < childs.size(); ++i)
            {
                if (i == c)
                    continue;

                sum += min(dy(sales, tree, childs[i], true), dy(sales, tree, childs[i], false));
            }

            min_sum = min(min_sum, sum);
        }

        return D[n][participate] = min_sum;
    }
}

long long solution(vector<int> sales, vector<vector<int>> links)
{
    vector<vector<int>> tree(sales.size());
    for (int i = 0; i < links.size(); ++i)
    {
        int from = links[i][0] - 1;
        int to = links[i][1] - 1;

        tree[from].push_back(to);
    }

    //print(tree);

    int root = 0;
    return  min(dy(sales, tree, root, false), dy(sales, tree, root, true));
}