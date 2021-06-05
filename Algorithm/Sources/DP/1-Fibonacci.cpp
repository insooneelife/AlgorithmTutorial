

#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

int mem[101] = {};
int Fibo(int n)
{
    if (n == 0)
        return 0;

    if (n == 1)
        return 1;

    if (mem[n] != 0)
        return mem[n];

    cout << n << " ";
    return mem[n] = Fibo(n - 1) + Fibo(n - 2);
}

// 이진트리를 이용한 메모이제이션
// O(NlogN)
int Fibo(map<int, int>& mem, int n)
{
    if (n == 0)
        return 0;

    if (n == 1)
        return 1;

    // 답을 한번이라도 구했다면, 바로 반환
    auto it = mem.find(n);
    if (it != end(mem))
        return it->second;

    // 최초로 답을 구하는 경우 배열에 저장
    int ans = Fibo(mem, n - 1) + Fibo(mem, n - 2);
    mem.insert(make_pair(n, ans));
    return ans;
}

// 배열과 반복문을 이용한 방법
int FiboIterate(int n)
{
    int mem[101] = { 0 };
    mem[0] = 0;
    mem[1] = 1;
    for (int i = 2; i <= n; ++i)
    {
        mem[i] = mem[i - 1] + mem[i - 2];
    }
    return mem[n];
}

int main()
{
    int t;
    cin >> t;

    cout << Fibo(t);

    return 0;

    
}