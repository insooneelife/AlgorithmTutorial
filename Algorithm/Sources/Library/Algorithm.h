#pragma once

#include "Headers.h"
#include "Utility.h"
#include "Data.h"


class Algorithm
{
public:
    // [1, n] 까지의 합
    // time complexity     O(1)
    // input               자연수 n
    // output              [1, n] 까지의 합
    long long Sum(long long n)
    {
        return n * (n + 1) / (long long)2; 
    }

    // [a, b] 까지의 합
    // time complexity     O(1)
    // input               정수 a, b (음수에서도 동작함)
    // output              [a, b] 까지의 합
    long long RangeSum(long long a, long long b)
    {
        if (a > b)
            std::swap(a, b);

        if (a >= 0)
        {
            return Sum(b) - Sum(a) + a;
        }
        else
        {
            return -Sum(abs(a)) + Sum(b);
        }
    }

    // p, q의 최대공약수를 구하는 알고리즘
    // time complexity     O(logN)
    // input               두 수 p, q
    // output              p, q의 최대공약수
    static long long GCD(long long p, long long q)
    {
        if (q == 0) return p;
        return GCD(q, p % q);
    }

    // N개의 수들의 최대공약수를 구하는 알고리즘
    // time complexity      O(N * logM) (M = smallest element in array)
    // input                N개의 수
    // output               N개의 수의 최대공약수
    static long long GCD(std::vector<long long> numbers)
    {
        int result = numbers[0];
        for (int i = 1; i < numbers.size(); i++)
        {
            result = GCD(numbers[i], result);

            if (result == 1)
            {
                return 1;
            }
        }
        return result;
    }

    // p, q의 최소공배수를 구하는 알고리즘
    // time complexity     O(logN)
    // input               두 수 p, q
    // output              p, q의 최소공배수
    static long long LCM(long long p, long long q)
    {
        return p * q / GCD(p, q);
    }

    // N개의 수들의 최소공배수를 구하는 알고리즘
    // time complexity      O(N * logM) (M = smallest element in array)
    // input                N개의 수
    // output               N개의 수의 최소공배수
    static long long LCM(std::vector<long long> numbers)
    {
        long long result = numbers[0];

        for (int i = 1; i < numbers.size(); i++)
            result = (numbers[i] * result) / (GCD(numbers[i], result));

        return result;
    }

    // n이 소수인지 판단하는 알고리즘
    // time complexity     O(N^0.5)
    // input               자연수 n
    // output              소수이면 true, 아니면 false
    static bool IsPrime(int n)
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

    // 모듈라 규칙
    class Modular
    {
    public:
        // (a + b) % m
        static long long Sum(long long a, long long b, long long m)
        {
            return ((a % m) + (b % m)) % m;
        }

        // (a - b) % m
        static long long Sub(long long a, long long b, long long m)
        {
            return ((a % m) - (b % m) + m) % m;
        }

        // (a * b) % m
        static long long Mul(long long a, long long b, long long m)
        {
            return ((a % m) * (b % m)) % m;
        }
    };

    class VectorOperations
    {
    public:
        std::vector<int> AddVec(const std::vector<int>& a, const std::vector<int>& b)
        {
            using namespace std;
            std::vector<int> c(a.size());
            for (int i = 0; i < a.size(); ++i)
            {
                c[i] = a[i] + b[i];
            }
            return c;
        }

        std::vector<int> SubVec(const std::vector<int>& a, const std::vector<int>& b)
        {
            using namespace std;
            vector<int> c(a.size());
            for (int i = 0; i < a.size(); ++i)
            {
                c[i] = a[i] - b[i];
            }
            return c;
        }

        std::vector<int> MulVec(const std::vector<int>& a, int k)
        {
            using namespace std;
            vector<int> c(a.size());
            for (int i = 0; i < a.size(); ++i)
            {
                c[i] = a[i] * k;
            }
            return c;
        }

        std::vector<int> MulVec(const std::vector<int>& a, const std::vector<int>& b)
        {
            using namespace std;
            vector<int> c(a.size());
            for (int i = 0; i < a.size(); ++i)
            {
                c[i] = a[i] * b[i];
            }
            return c;
        }

        std::vector<int> DivVec(const std::vector<int>& a, int k)
        {
            using namespace std;
            vector<int> c(a.size());
            for (int i = 0; i < a.size(); ++i)
            {
                c[i] = a[i] / k;
            }
            return c;
        }

        std::vector<int> DivVec(const std::vector<int>& a, const std::vector<int>& b)
        {
            using namespace std;
            vector<int> c(a.size());
            for (int i = 0; i < a.size(); ++i)
            {
                c[i] = a[i] / b[i];
            }
            return c;
        }
    };

    // n 이하의 모든 소수를 생성하는 알고리즘
    // time complexity     O(N)
    // space complexity    O(N) 
    // input               자연수 n
    // output              n 이하의 모든 소수
    class Eratosthenes
    {
    public:
        Eratosthenes(size_t n) : n(n) {}

        void Make()
        {
            primes.resize(n + 1, true);
            primes[0] = primes[1] = false;

            int sqrtn = (int)(sqrt(n));
            for (int i = 2; i <= sqrtn; ++i)
            {
                if (!primes[i]) continue;

                for (int j = i * i; j <= n; j += i)
                {
                    primes[j] = false;
                }
            }
        }

        // O(1)
        bool IsPrime(int n) const
        {
            return primes[n];
        }

        void Print() const
        {
            for (int i = 2; i <= n; ++i)
            {
                if (primes[i])
                {
                    std::cout << i << " ";
                }
            }
        }

    private:
        size_t n;
        std::vector<bool> primes;
    };

    // 소인수 생성을 위한 전처리 알고리즘
    // time complexity     O(N)
    // space complexity    O(N) 
    // input               소수 생성 범위 n
    // output              n 이하의 모든 소수
    class EratosthenesFactors
    {
    public:
        EratosthenesFactors(size_t n) : n(n) 
        {
            Make();
        }

        void Make()
        {
            factors.resize(n + 1);
            factors[0] = factors[1] = -1;

            for (int i = 2; i <= n; ++i)
            {
                factors[i] = i;
            }

            int sqrtn = (int)(sqrt(n));
            for (int i = 2; i <= sqrtn; ++i)
            {
                if (factors[i] != i) continue;

                for (int j = i * i; j <= n; j += i)
                {
                    if (factors[j] == j)
                    {
                        factors[j] = i;
                    }
                }
            }
        }

        int Get(int n) const
        {
            return factors[n];
        }

    private:
        size_t n;
        std::vector<int> factors;
    };

    // 2 이상의 자연수 n을 소인수분해하는 알고리즘
    // EratosthenesFactors에 최소 소인수가 미리 생성되어 있어야 정상동작한다.
    // time complexity     O(N)
    // space complexity    O(N) 
    // input               자연수 n
    // output              n의 모든 소인수
    static std::vector<int> Factors(const EratosthenesFactors& era, int n)
    {
        using namespace std;

        vector<int> ret;

        while (n > 1)
        {
            int min_factor = era.Get(n);
            ret.push_back(min_factor);
            n /= min_factor;
        }
        return ret;
    }
    
    // 2 이상의 자연수 n을 소인수분해하는 알고리즘
    // time complexity     O(N^0.5)
    // input               자연수 n
    // output              n의 모든 소인수
    static std::vector<int> Factors(int n)
    {
        using namespace std;

        vector<int> ret;
        int sqrtn = (int)(sqrt(n));

        for (int i = 2; i <= sqrtn; ++i)
        {
            while (n % i == 0)
            {
                n /= i;
                ret.push_back(i);
            }
        }
        if (n > 1)ret.push_back(n);
        return ret;
    }

    static int CalcDivisors(int n)
    {
        using namespace std;
        const vector<int>& factors = Factors(n);

        map<int, int> counts;
        for (int f : factors)
        {
            counts[f]++;
        }
        
        int mul = 1;
        for (auto e : counts)
        {
            mul *= (e.second + 1);
        }

        return mul;
    }

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

    // BigInteger
    // C++로 BigInteger 문제를 푸는것은 어리석은 짓이다.
    // python으로 풀도록 하자.


    // [0, N - 1] 범위의 수 중, K개를 선택하는 모든 조합 (재귀)
    // time complexity     O(C(N, K) * K)
    // input               자연수 N, K
    // output              모든 조합
    class Combinations
    {
    public:
        Combinations(const int N, const int K) : N(N), K(K) 
        {
            Make();
        }

        void Make()
        {
            Make(K);
        }

    private:
        void Make(int k)
        {
            using namespace std;

            if (k == 0)
            {
                all_combs.push_back(combs);
                return;
            }

            int start = combs.size() > 0 ? combs.back() + 1 : 0;
            for (int i = start; i < N; ++i)
            {
                combs.push_back(i);
                Make(k - 1);
                combs.pop_back();
            }
        }

    public:
        std::vector<std::vector<int>> all_combs;

    private:
        const int N;
        const int K;
        std::vector<int> combs;
    };
        

    // [0, N - 1] 범위의 수 중, K개를 선택하는 모든 조합 (반복문)
    // time complexity     O(C(N, K) * K)
    // input               자연수 N, K
    // output              모든 조합
    static void CombinationsIterate(const int N, const int K, std::vector<std::vector<int>>& all_combs)
    {
        using namespace std;

        vector<int> combs(K);
        if (K == 0)
        {
            all_combs.push_back(combs);
            return;
        }

        for (int i = 0; i < K; i++)
        {
            combs[i] = i;
        }

        while (combs[K - 1] < N)
        {
            all_combs.push_back(combs);

            int t = K - 1;
            while (t != 0 && combs[t] == N - K + t)
            {
                t--;
            }

            combs[t]++;

            for (int i = t + 1; i < K; i++)
            {
                combs[i] = combs[i - 1] + 1;
            }
        }
    }

    // 괄호의 유효성 여부 판단
    // time complexity     O(N)
    // input               괄호 문자열 "[]{([]){}}"
    // output              유효성 여부
    static bool IsBracketValid(const std::string& s)
    {
        using namespace std;
        map<char, char> mapping = { {'[', ']'}, {'(', ')'}, {'{', '}' } };
        stack<char> st;
        int i = 0;
        st.push(s[i++]);

        while (i < s.size())
        {
            char c = s[i++];
            if (st.size() > 0)
            {
                char top = st.top();
                if (mapping[top] == c)
                {
                    st.pop();
                    continue;
                }
            }
            st.push(c);
        }

        return st.empty();
    }

    // 문자열 s가 회문인지 판별
    // time complexity     O(N)
    // input               문자열
    // output              회문 여부
    static bool IsPalindrome(const std::string& s)
    {
        for (int i = 0; i < s.size() / 2; ++i)
        {
            if (s[i] != s[s.size() - 1 - i])
                return false;
        }
        return true;
    }

    // 문자열 str의 모든 시작위치 s로부터 길이 len의 부분문자열이 회문인지 판별
    // time complexity     O(N ^ 2)
    // input               문자열
    // output              인덱스 s로 시작하는 길이 len인 모든 부분문자열의 회문 여부
    static void Palindrome(const std::string& str, std::vector<std::vector<bool>>& mem)
    {
        using namespace std;
        mem.resize(str.size(), vector<bool>(str.size() + 1, false));

        // 길이 0, 1, 2 palindrome 전처리
        for (int s = 0; s < str.size(); ++s)
        {
            mem[s][0] = false;
            mem[s][1] = true;
            if (s + 1 < str.size())
                mem[s][2] = str[s] == str[s + 1];
        }

        // 길이 3 palindrome 판별
        // 길이 4 palindrome 판별
        // ...
        // 길이 N palindrome 판별
        for (int len = 3; len <= str.size(); ++len)
        {
            for (int s = 0; s + len - 1 < str.size(); ++s)
            {
                mem[s][len] = mem[s + 1][len - 2] && (str[s] == str[s + len - 1]);
            }
        }
    }

    // 이항 계수
    class Coeff
    {
    public:
        Coeff(int n, int k) : C(n + 1, std::vector<long long>(k + 1, 0LL))
        {
            Make(n, k);
        }

        long long Get(int n, int k) const { return C[n][k]; }

    private:
        long long Make(int n, int k)
        {
            if (k == 0)
                return 1;
            if (n == k)
                return 1;

            if (C[n][k] != 0)
                return C[n][k];

            return C[n][k] = Make(n - 1, k - 1) + Make(n - 1, k);
        }

    private:
        std::vector<std::vector<long long>> C;
    };

    // 카탈란 수
    static long long Catalan(int n)
    {
        Coeff coeff(2 * n, n);

        // 카탈란 수
        return coeff.Get(2 * n, n) / (long long)(n + 1);
    }

    // 맨하탄 거리
    static int ManhatanDis(Vec<int> a, Vec<int> b)
    {
        return abs(a.x - b.x) + abs(a.y - b.y);
    }
};