
// 올바른 괄호의 개수
// https://programmers.co.kr/learn/courses/30/lessons/12929

#include <iostream>
#include <vector>
using namespace std;

class Coeff
{
public:
    Coeff(int n, int k) : C(n + 1, std::vector<int>(k + 1, 0)) 
    {
        Make(n, k);
    }

    long long Get(n, k) const { return C[n][k]; }

private:
    long long Make(int n, int k)
    {
        if (k == 0)
            return 1;
        if (n == k)
            return 1;

        if (C[n][k] != 0)
            return C[n][k];

        return C[n][k] = Coeff(n - 1, k - 1) + Coeff(n - 1, k);
    }

private:
    std::vector<std::vector<long long>> C;
};

int solution(int n) 
{
    Coeff coeff(2 * n, n);

    // 카탈란 수
    return coeff.Get(2 * n, n) / (n + 1);
}

int main() 
{

    cout << solution(3);
    return 0;
}


