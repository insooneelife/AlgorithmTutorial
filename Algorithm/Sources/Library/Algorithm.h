#pragma once

#include <iostream>
#include <vector>


class Algorithm
{
public:
    // p, q�� �ִ������� ���ϴ� �˰���
    // time complexity     O(logN)
    // input               �� �� p, q
    // output              p, q�� �ִ�����
    static int GCD(int p, int q)
    {
        if (q == 0) return p;
        return GCD(q, p % q);
    }

    // n�� �Ҽ����� �Ǵ��ϴ� �˰���
    // time complexity     O(N^0.5)
    // input               �ڿ��� n
    // output              �Ҽ��̸� true, �ƴϸ� false
    static bool IsPrime(int n)
    {
        if (n <= 1)
            return false;

        if (n == 2)
            return true;

        if (n % 2 == 0)
            return false;

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

    // ���� ��Ģ
    class Modular
    {
        // (a + b) % m
        static int Sum(int a, int b, int m)
        {
            return ((a % m) + (b % m)) % m;
        }

        // (a - b) % m
        static int Sub(int a, int b, int m)
        {
            return ((a % m) - (b % m) + m) % m;
        }

        // (a * b) % m
        static int Mul(int a, int b, int m)
        {
            return ((a % m) * (b % m)) % m;
        }
    };

    // n ������ ��� �Ҽ��� �����ϴ� �˰���
    // time complexity     O(N)
    // space complexity    O(N) 
    // input               �ڿ��� n
    // output              n ������ ��� �Ҽ�
    class Eratosthenes
    {
    public:
        Eratosthenes(size_t n) : n(n) {}

        void Make()
        {
            primes.resize(n + 1);
            primes[0] = primes[1] = false;

            for (int i = 2; i <= n; ++i)
            {
                primes[i] = i;
            }

            int sqrtn = (int)(sqrt(n));
            for (int i = 2; i <= sqrtn; ++i)
            {
                if (primes[i] != i) continue;

                for (int j = i * i; j <= n; j += i)
                {
                    if (primes[j] == j)
                        primes[j] = false;
                }
            }
        }

        bool IsPrime(int n) const
        {
            return primes[n] != 0;
        }

        void Print() const
        {
            for (int i = 2; i <= n; ++i)
            {
                if (primes[i] != 0)
                {
                    std::cout << primes[i] << " ";
                }
            }
        }

    private:
        size_t n;
        std::vector<int> primes;
    };

    // ���μ� ������ ���� ��ó�� �˰���
    // time complexity     O(N)
    // space complexity    O(N) 
    // input               �Ҽ� ���� ���� n
    // output              n ������ ��� �Ҽ�
    class EratosthenesFactors
    {
    public:
        EratosthenesFactors(size_t n) : n(n) {}

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

    // 2 �̻��� �ڿ��� n�� ���μ������ϴ� �˰���
    // EratosthenesFactors�� �ּ� ���μ��� �̸� �����Ǿ� �־�� �������Ѵ�.
    // time complexity     O(N)
    // space complexity    O(N) 
    // input               �ڿ��� n
    // output              n�� ��� ���μ�
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
    
    // 2 �̻��� �ڿ��� n�� ���μ������ϴ� �˰���
    // time complexity     O(N^0.5)
    // input               �ڿ��� n
    // output              n�� ��� ���μ�
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

    // 10���� -> N���� ��ȯ
    class DecimalNumberSystem
    {
    public:
        // input : 10 ���� n, ��ȯ ��� ���� num_system [2 - 16]
        // output : num_system ����
        static std::string Convert(long long n, int num_system)
        {
            using namespace std;

            char arr[100];
            int k = 0;

            if (n == 0)
                return "0";

            while (n)
            {
                arr[k++] = ToASCII(n % num_system);
                n /= num_system;
            }

            string out = "";
            for (int i = k - 1; i >= 0; i--)
            {
                out += arr[i];
            }
            return out;
        }

    private:
        static char ToASCII(char n)
        {
            if (n < 10) return '0' + n;
            else return 'A' + n - 10;
        }
    };

    // BigInteger
    // C++�� BigInteger ������ Ǫ�°��� ����� ���̴�.
    // python���� Ǯ���� ����.


    // [0, N - 1] ������ �� ��, K���� �����ϴ� ��� ���� (���)
    // time complexity     O(C(N, K) * K)
    // input               �ڿ��� N, K
    // output              ��� ����
    class Combinations
    {
    public:
        Combinations(const int N, const int K) : N(N), K(K) {}

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
        

    // [0, N - 1] ������ �� ��, K���� �����ϴ� ��� ���� (�ݺ���)
    // time complexity     O(C(N, K) * K)
    // input               �ڿ��� N, K
    // output              ��� ����
    static void CombinationsIterate(const int N, const int K, std::vector<std::vector<int>>& all_combs)
    {
        using namespace std;

        vector<int> combs(K);
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

};