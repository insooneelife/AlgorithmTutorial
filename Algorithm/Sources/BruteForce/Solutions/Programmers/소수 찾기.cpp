// 소수 찾기 (순열, 정수론)
// https://programmers.co.kr/learn/courses/30/lessons/42839


// 방법 1.
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <map>

#include "Algorithm.h"

using namespace std; 




void CollectPrimes(const string& v, const Algorithm::Eratosthenes& era, vector<int>& primes)
{
    for (int j = 0; j < v.size(); ++j)
    {
        string number(begin(v), begin(v) + j + 1);
        int num = stoi(number);            

        if(era.IsPrime(num))
        {
            primes.push_back(num);
        }
    }    
}

int solution(string numbers) 
{
    Algorithm::Eratosthenes era(10000000);
    era.Make();
        
    vector<int> primes;
    set<int> collections;

    sort(begin(numbers), end(numbers));

    do
    {
        CollectPrimes(numbers, era, primes);

        for (auto e : primes)
        {
            collections.insert(e);
        }
    } while (next_permutation(begin(numbers), end(numbers)));

    return collections.size();
}



int main()
{
    string numbers = "17";
    //string numbers = "011";

    int answer = solution(numbers);
    cout << answer;
    
    return 0;
}





// 방법 2.
#include <iostream>
#include <vector>
#include <set>
#include "Print.h"

using namespace std;


const int kNum = 7;
bool selected[kNum + 1];

void Permutation(vector<vector<int>>& all_perms, vector<int>& permutations, int n, int k)
{
    if (permutations.size() == k)
    {
        //Print::Container(permutations);
        all_perms.push_back(permutations);
    }

    for (int i = 1; i <= n; ++i)
    {
        if (!selected[i])
        {
            permutations.push_back(i);
            selected[i] = true;

            Permutation(all_perms, permutations, n, k);

            permutations.pop_back();
            selected[i] = false;
        }
    }
}

void Permutation(vector<vector<int>>& all_perms, int n, int k)
{
    vector<int> permutations;
    Permutation(all_perms, permutations, n, k);
}

bool IsPrime(int n)
{
    if (n <= 1)
        return false;

    // 2는 예외
    if (n == 2)
        return true;

    // 모든 짝수는 2의 배수니까 소수 x
    if (n % 2 == 0)
        return false;

    // 3 5 7 9 ...
    int sqrtn = (int)(sqrt(n));
    for (int i = 3; i <= sqrtn; i += 2)
    {
        if (n % i == 0)
        {
            return false;
        }
    }
    return true;
}

int solution(string numbers)
{
    set<int> primes;
    for (int i = 1; i <= numbers.size(); ++i)
    {
        vector<vector<int>> all_perms;
        Permutation(all_perms, numbers.size(), i);

        for (const vector<int>& v : all_perms)
        {
            string number = "";
            for (int j = 0; j < v.size(); ++j)
            {
                int index = v[j] - 1;
                number += numbers[index];
            }

            int num = stoi(number);
            if (IsPrime(num))
            {
                primes.insert(num);
            }
        }
    }

    return primes.size();
}

int main()
{
    string numbers = "17";
    //string numbers = "011";

    cout << solution(numbers);

    return 0;
}