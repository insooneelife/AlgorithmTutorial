// 순열

// 순열 예제1
// 재귀함수로 순열 알고리즘 구현
























#include <iostream>
#include <vector>
#include "Utility.h"
using namespace std;


// 메모리를 이용하면 조금 쉽게 갈 수 있음
// 1부터 N까지의 정수를 모두 한번씩 선택해봄.
// i1를 선택한 경우,
// i1을 제외한 1부터 N까지의 정수를 모두 한번씩 선택해봄.
// i2를 선택한 경우,
// i1, i2를 제외한 1부터 N까지의 정수를 모두 한번씩 선택해봄.
// ...
const int kNum = 4;
bool selected[kNum + 1];

void Permutation(vector<int>& permutations)
{
    if (permutations.size() == kNum)
    {
        Print::Container(permutations);
    }

    for (int i = 1; i <= kNum; ++i)
    {
        if (!selected[i])
        {
            permutations.push_back(i);
            selected[i] = true;

            Permutation(permutations);

            permutations.pop_back();
            selected[i] = false;
        }
    }
}

void PermutationSTL()
{
    vector<int> permutations = { 1, 2, 3, 4 };

    do
    {
        Print::Container(permutations);

    } while (next_permutation(permutations.begin(), permutations.end()));
}

int main()
{
    vector<int> permutations;
    Permutation(permutations);

    cout << endl;

    PermutationSTL();

    return 0;
}

// next_permutation 주의점
// next_permutation은 넣은 컨테이너의 상태부터 순열을 만들기 때문에,
// {1, 2, 3, 4, 5} 를 넣었을 때의 결과값과
// {5, 4, 3, 2, 1} 을 넣었을 때의 결과값이 다르다.
// 이러한 문제는 문자열의 순열을 만들고 싶을 때 많이 발생한다.
// "301", "103" 을 넣었을 때 순열은 서로 다르다.
// 이게 같게 나오길 바란다면 먼저 오름차순으로 sort를 해주어야 한다.