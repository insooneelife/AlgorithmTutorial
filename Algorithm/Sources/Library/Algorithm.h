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
            swap(a, b);

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
    static long long GCD(vector<long long> numbers)
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
    static long long LCM(vector<long long> numbers)
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

    /*
    // 인풋을 통해 인접리스트 그래프를 생성한다.
    static std::vector<std::vector<int>> MakeAdjListGraphFromInput(
        int N,
        const std::vector<std::vector<int>>& input,
        bool bigraph = true)
    {
        using namespace std;
        vector <vector<int>> graph(N + 1);
        for (const vector<int>& adj : input)
        {
            int from = adj[0];
            int to = adj[1];
            int cost = adj[2];

            graph[from].push_back(to);
            if (bigraph)
            {
                graph[to].push_back(from);
            }
        }

        return graph;
    }
    */

    // 인풋을 통해 인접행렬 그래프를 생성한다.
    // input    2D Array Size N, 간선(노드는 1부터 시작), 양방향 여부
    // output   인접행렬 그래프
    static std::vector<std::vector<long long>> MakeAdjArrayGraphFromInput(
        const int N,
        std::vector<std::vector<int>> inputs,
        bool bigraph = true)
    {
        using namespace std;
        vector<vector<long long>> graph(N, vector<long long>(N, std::numeric_limits<int>::max()));

        for (int i = 0; i < inputs.size(); ++i)
        {
            int from = inputs[i][0] - 1;
            int to = inputs[i][1] - 1;
            int cost = inputs[i][2];

            graph[from][to] = (long long)cost;
            if (bigraph)
            {
                graph[to][from] = (long long)cost;
            }
        }
        return graph;
    }

    // 특정 조건에 맞는
    // 인접행렬 그래프를 생성한다.
    static std::vector<std::vector<int>> MakeAdjArrayGraph(const int N)
    {
        using namespace std;

        vector<vector<int>> graph(N, vector<int>(N, 0));

        for (int from = 0; from < N; ++from)
        {
            for (int to = 0; to < N; ++to)
            {
                // 여기에 조건 추가
                bool other_conditions_here = true;
                if (from == to || other_conditions_here)
                {
                    graph[from][to] = 1;
                    graph[to][from] = 1;
                }
            }
        }
    }

    // 2D 배열판 탐색 경로를 구한다.
    // 단, 탐색중에 backtrack 정보를 생성하며 탐색해야한다.
    // input        backtrack 정보, 마지막 방문 위치
    // output       탐색 경로
    static vector<Vec<int>> MakeSearchPath(const map<Vec<int>, Vec<int>>& backtrack, Vec<int> last)
    {
        using namespace std;
        vector<Vec<int>> path;
        Vec<int> node = last;
        while (!(node == backtrack.at(node)))
        {
            path.push_back(node);
            node = backtrack.at(node);
        }
        path.push_back(node);

        reverse(begin(path), end(path));

        return path;
    }

    // 2D 배열(게임판) 깊이우선탐색
    // time complexity     O(N ^ 2)
    // input               2D 배열(N ^ 2), 방문기록 배열(N ^ 2), 탐색 가능한 값, 탐색시작 위치
    // available(1)은 갈 수 있는 길이고, 그 외는 갈 수 없는 값이다.
    // { 1, 0, 1, 1, 1 },
    // { 1, 0, 1, 0, 1 },
    // { 1, 0, 1, 1, 1 },
    // { 1, 1, 1, 0, 1 },
    // { 0, 0, 0, 0, 1 }
    // output              방문한 노드 수, 방문기록
    static int DFS(
        const std::vector<std::vector<int>>& board,
        std::vector<std::vector<bool>>& visited,
        const int available, 
        int i, 
        int j)
    {
        using namespace std;

        const int M = board.size();
        const int N = board[0].size();

        if (visited[i][j])
            return 0;

        const vector<pair<int, int>> directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
        int cnt = 1;
        visited[i][j] = true;

        for (auto p : directions)
        {
            int nexti = i + p.first;
            int nextj = j + p.second;

            if (!Utility::InArray2D(M, N, nexti, nextj))
                continue;

            if (board[nexti][nextj] == available && !visited[nexti][nextj])
                cnt += DFS(board, visited, available, nexti, nextj);

        }
        return cnt;
    }

    // 그래프(인접행렬) 깊이우선탐색
    // time complexity     O(N ^ 2)
    // input               인접행렬 그래프(N ^ 2), 방문기록 배열(N), 탐색시작 노드
    // { 1, 1, 0 },
    // { 1, 1, 0 },
    // { 0, 0, 1 }
    // output              방문한 노드 수, 방문기록
    static int DFS(
        const std::vector<std::vector<int>>& graph,
        std::vector<bool>& visited,
        int node)
    {
        using namespace std;

        if (visited[node])
            return 0;

        const int N = graph.size();
        int cnt = 1;
        visited[node] = true;

        for (int i = 0; i < N; ++i)
        {
            if (graph[node][i] == 1 && !visited[i])
                cnt += DFS(graph, visited, i);
        }
        return cnt;
    }

    // 2D 배열(게임판) 너비우선탐색
    // time complexity     O(N ^ 2)
    // input               2D 배열(N ^ 2), 탐색시작 위치, 탐색중단 위치
    // 1은 갈 수 있는 길이고, 0은 갈 수 없는 길이다.
    // { 1, 0, 1, 1, 1 },
    // { 1, 0, 1, 0, 1 },
    // { 1, 0, 1, 1, 1 },
    // { 1, 1, 1, 0, 1 },
    // { 0, 0, 0, 0, 1 }
    // output              최단방문회수(길이 없는 경우 : -1)
    static int BFS(const std::vector<std::vector<int>>& maps, Vec<int> from, Vec<int> to)
    {
        using namespace std;
        const int CanMove = 1;
        const int rows = maps.size();
        const int columns = maps[0].size();
        const vector<Vec<int>> directions = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
        vector<vector<bool>> visited(rows, vector<bool>(columns, false));
        queue<State> que;

        int ret = -1;

        que.push({ from.x, from.y, 1 });
        visited[from.x][from.y] = true;

        while (!que.empty())
        {
            State state = que.front();

            if (state.i == to.x && state.j == to.y)
            {
                ret = state.cnt;
                break;
            }

            for (auto d : directions)
            {
                int nexti = state.i + d.x;
                int nextj = state.j + d.y;

                if (Utility::InArray2D(rows, columns, nexti, nextj) &&
                    maps[nexti][nextj] == CanMove &&
                    !visited[nexti][nextj])
                {
                    que.push({ nexti, nextj, state.cnt + 1 });
                    visited[nexti][nextj] = true;
                }
            }
            que.pop();
        }

        return ret;
    }


    // 2D 배열(게임판) 너비우선탐색 + 경로생성
    static int BFS(const std::vector<std::vector<int>>& maps, Vec<int> from, Vec<int> to, vector<Vec<int>>& path)
    {
        using namespace std;
        const int CanMove = 1;
        const int rows = maps.size();
        const int columns = maps[0].size();
        const vector<Vec<int>> directions = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
        vector<vector<bool>> visited(rows, vector<bool>(columns, false));
        queue<State> que;
        map<Vec<int>, Vec<int>> backtrack;
        backtrack.insert(make_pair(from, from));

        int ret = -1;

        que.push({ from.x, from.y, 1 });
        visited[from.x][from.y] = true;

        while (!que.empty())
        {
            State state = que.front();

            if (state.i == to.x && state.j == to.y)
            {
                ret = state.cnt;
                path = MakeSearchPath(backtrack, to);
                break;
            }

            for (auto d : directions)
            {
                int nexti = state.i + d.x;
                int nextj = state.j + d.y;

                if (Utility::InArray2D(rows, columns, nexti, nextj) &&
                    maps[nexti][nextj] == CanMove &&
                    !visited[nexti][nextj])
                {
                    que.push({ nexti, nextj, state.cnt + 1 });
                    visited[nexti][nextj] = true;
                    backtrack.insert(make_pair<Vec<int>, Vec<int>>({ nexti, nextj }, { state.i, state.j }));
                }
            }
            que.pop();
        }

        return ret;
    }


    // 그래프(인접행렬) 너비우선탐색
    // time complexity     O(N ^ 2)
    // input               인접행렬 그래프(N ^ 2), 탐색시작 노드, 탐색중단 노드
    // { 1, 1, 0 },
    // { 1, 1, 0 },
    // { 0, 0, 1 }
    // output              최단방문회수(길이 없는 경우 : -1)
    static int BFS(const std::vector<std::vector<int>>& graph, int start, int finish)
    {
        using namespace std;
        using Node = pair<int, int>;

        const int N = graph.size();
        vector<bool> visited(N, false);
        queue<Node> que;
        int ret = -1;

        que.push({ start, 1 });
        visited[start] = true;

        while (!que.empty())
        {
            Node state = que.front();
            int node = state.first;
            int cnt = state.second;

            if (node == finish)
            {
                ret = cnt;
                break;
            }

            for (int next = 0; next < N; ++next)
            {
                if (graph[node][next] == 1 && !visited[next])
                {
                    que.push({ next, cnt + 1 });
                    visited[next] = true;
                }
            }

            que.pop();
        }

        return ret;
    }

    

    // 플로이드 알고리즘
    // input        인접행렬 그래프 (node는 1부터 시작)
    // output       모든 정점 쌍에 대한 최단거리
    class Floyd
    {
    public:
        Floyd(const int N, std::vector<std::vector<int>> inputs) : N(N), adj(MakeAdjArrayGraphFromInput(N, inputs))
        {
            Make();
        }

        int GetCost(int from, int to) const
        {
            return adj[from - 1][to - 1];
        }

    private:
        void Make()
        {
            for (int i = 0; i < N; ++i)
                adj[i][i] = 0;

            for (int k = 0; k < N; ++k)
                for (int i = 0; i < N; ++i)
                    for (int j = 0; j < N; ++j)
                        adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
        }

    private:
        const int N;
        std::vector<std::vector<long long>> adj;
    };
};