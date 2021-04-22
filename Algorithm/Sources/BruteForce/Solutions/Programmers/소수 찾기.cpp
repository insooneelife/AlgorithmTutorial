// 소수 찾기 (순열, 정수론)
// https://programmers.co.kr/learn/courses/30/lessons/42839

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



