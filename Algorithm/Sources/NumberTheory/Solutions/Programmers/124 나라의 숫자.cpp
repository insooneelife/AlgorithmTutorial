// 124 나라의 숫자
// https://programmers.co.kr/learn/courses/30/lessons/12899

// 시행착오
// 1. 0011 의 경우 Convert를 이용하면 11로 표현된다. 현재 이 문제에서는 0 또한 중요한 정보이므로 제거하면 안된다.
// 2. setfill을 이용할 때 endl을 주의
// 3. 라이브러리 ToNumber 코드 long long으로 변경

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <cmath>

using namespace std;

// 10진수 -> N진수 변환
// N진수 -> 10진수 변환
// (36진수까지 허용)
class DecimalNumberSystem
{
public:
    // input : 10-진수 n, 변환 대상 진수 num_system [2 - 36]
    // output : num_system-진수 값
    static std::string Convert(long long num, int num_system)
    {
        using namespace std;

        string out = "";
        if (num == 0)
            return "0";

        while (num)
        {
            out += ToASCII(num % num_system);
            num /= num_system;
        }

        reverse(begin(out), end(out));
        return out;
    }

    // input : number_system-진수 num, 변환 대상 진수 10
    // output : 10-진수 값
    static long long ToDecimal(const std::string& val, int num_system)
    {
        long long out = 0;
        long long mul = 1;
        for (int i = val.size() - 1; i >= 0; --i)
        {
            char n = val[i];
            long long num = ToNumber(n);

            out += num * mul;
            mul *= (long long)num_system;
        }

        return out;
    }

private:
    static char ToASCII(int n)
    {
        if (n < 10) return '0' + n;
        else return 'A' + n - 10;
    }

    static long long ToNumber(char n)
    {
        if ('0' <= n && n <= '9') return (long long)n - (long long)'0';
        else return (long long)(n - 'A') + 10LL;
    }
};

string solution(int N) 
{
    int k = 0;
    long long n = N;
    long long sum = 0;
    while (n > sum)
    {
        k++;
        sum += pow(3, k);
    }

    long long prev = sum - pow(3, k);
    long long left = n - prev;

    string tri = DecimalNumberSystem::Convert(left - 1, 3);

    stringstream ss;
    ss << setfill('0') << setw(k) << tri;
    tri = ss.str();

    for (int i = 0; i < tri.size(); ++i)
    {
        char c = tri[i];
        if (c == '0')
        {
            tri[i] = '1';
        }
        else if (c == '1')
        {
            tri[i] = '2';
        }
        else
        {
            tri[i] = '4';
        }
    }

    //cout << sum << " " << k << " " << prev << " " << left << " " << tri;

    return tri;
}


int main()
{
    int n = 4;
    string answer = solution(n);

    cout <<answer;

    return 0;
}