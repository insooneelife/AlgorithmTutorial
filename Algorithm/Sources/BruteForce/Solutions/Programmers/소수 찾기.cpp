// 소수 찾기 (순열, 정수론)
// https://programmers.co.kr/learn/courses/30/lessons/42839

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <map>

using namespace std; 

class Eratosthenes
{
public:
    Eratosthenes(size_t n) : n(n) {}

    void Make()
    {
        primes.resize(n + 1);

        for (int i = 2; i <= n; ++i)
        {
            primes[i] = i;
        }

        for (int i = 2; i <= n; ++i)
        {
            if (primes[i] == 0) continue;

            for (int j = 2 * i; j <= n; j += i)
            {
                primes[j] = 0;
            }
        }
    }

    void Print()
    {
        for (int i = 2; i <= n; ++i)
        {
            if (primes[i] != 0)
            {
                cout << primes[i] << " ";
            }
        }
    }

    bool IsPrime(int n) const
    {
        return primes[n] != 0;
    }

private:
    size_t n;
    vector<int> primes;
};

class Print
{
private:
    const static string kTag;

public:
    template <typename T, typename U>
    static void Map(const map<T, U>& container, string tag = kTag)
    {
        cout << tag << endl;
        for (auto e : container)
        {
            cout << e.first << " " << e.second << endl;
        }
        cout << endl;
    }

    template <typename T>
    static void Container(const T& container, string tag = kTag)
    {
        cout << tag << endl;
        for (auto e : container)
        {
            cout << e << " ";
        }
        cout << endl;
    }

    template <typename CustomType>
    static void Custom(const vector<CustomType>& container, string tag = kTag)
    {
        cout << tag << endl;
        for (auto e : container)
        {
            e.Print();
        }
        cout << endl;
    }
};
const string Print::kTag = "------------------------------------";



void CollectPrimes(const string& v, const Eratosthenes& era, vector<int>& primes)
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
    Eratosthenes era(10000000);
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



