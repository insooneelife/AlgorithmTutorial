
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cmath>

//#include "Utility.h"
//#include "Algorithm.h"
//#include "Print.h"

using namespace std;

int arr[100][100] = {};

struct Vec
{
    int i;
    int j;
};

int Rotate(vector<int>& query)
{
    int si = query[0] - 1;
    int sj = query[1] - 1;
    int fi = query[2] - 1;
    int fj = query[3] - 1;
    int qrows = fi - si;
    int qcolumns = fj - sj;
    int minval = numeric_limits<int>::max();

    const vector<Vec> directions = { {1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    const vector<int> movecounts = { qrows, qcolumns, qrows, qcolumns - 1 };

    for (int i = 0; i < directions.size(); ++i)
    {
        Vec dir = directions[i];
        int moves = movecounts[i];

        for (int j = 0; j < moves; ++j)
        {
            int nexti = si + dir.i;
            int nextj = sj + dir.j;
            swap(arr[si][sj], arr[nexti][nextj]);

            minval = min(arr[si][sj], minval);
            minval = min(arr[nexti][nextj], minval);

            si = nexti;
            sj = nextj;
        }
    }
    return minval;
}

vector<int> solution(int rows, int columns, vector<vector<int>> queries) 
{
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {
            arr[i][j] = (i * columns + j) + 1;
        }
    }

    vector<int> answer;
    for (auto q : queries)
    {
        int minval = Rotate(q);
        answer.push_back(minval);
    }

    return answer;
}

int main()
{
    int rows = 6;
    int columns = 6;
    vector<vector<int>> queries =
    {
        {2,2,5,4} ,{3,3,6,6},{5,1,6,3}
    };
    
    vector<int> answer = solution(rows, columns, queries);
    //Print::Container(answer);


    return 0;
}





