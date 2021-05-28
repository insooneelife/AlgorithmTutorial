
// 행렬 제곱
// https://www.acmicpc.net/problem/10830

// 시행착오
// 1. n, b  long long 인풋
// 2. 첫 인풋이 1000인 경우, p가 1일 때, 모듈러가 되지 않은 상태로 반환될 수 있음 (스택오버플로우 문제는 아니었음)

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <random>

using namespace std;
using ll = long long;


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

template <typename T>
struct Matrix
{
    Matrix() {}
    Matrix(int rows, int columns) : m(rows, vector<T>(columns, 0)) {}
    
    int GetRows() const { return m.size(); }
    int GetColumns() const { return m[0].size(); }

    void Print() const
    {
        for (int i = 0; i < GetRows(); ++i)
        {
            for (int j = 0; j < GetColumns(); ++j)
            {
                cout << m[i][j] << " ";
            }
            cout << endl;
        }
    }


    static Matrix Input(Matrix& mat)
    {
        for (int i = 0; i < mat.GetRows(); ++i)
            for (int j = 0; j < mat.GetColumns(); ++j)
                cin >> mat.m[i][j];

        return mat;
    }


    static Matrix Add(const Matrix& a, const Matrix& b)
    {
        Matrix out(a.GetRows(), a.GetColumns());
        Add(a, b, out);
        return out;
    }

    static Matrix Sub(const Matrix& a, const Matrix& b)
    {
        Matrix out(a.GetRows(), a.GetColumns());
        Sub(a, b, out);
        return out;
    }

    static Matrix Mul(const Matrix& a, T k)
    {
        Matrix out(a.GetRows(), a.GetColumns());
        Mul(a, k, out);
        return out;
    }

    static Matrix Mod(const Matrix& a, long long k)
    {
        Matrix out(a.GetRows(), a.GetColumns());
        Mod(a, k, out);
        return out;
    }

    static Matrix Mul(const Matrix& a, const Matrix& b)
    {
        const int ARows = a.GetRows();
        const int AColumns = a.GetColumns();
        const int BColumns = b.GetColumns();

        Matrix out(a.GetRows(), a.GetColumns());

        for (int k = 0; k < BColumns; ++k)
        {
            for (int i = 0; i < ARows; ++i)
            {
                for (int j = 0; j < AColumns; ++j)
                {
                    out.m[i][k] += a.m[i][j] * b.m[j][k];
                }

                out.m[i][k] %= 1000;
            }
        }
        return out;
    }

    static Matrix Identity(int n)
    {
        Matrix mat(n, n);

        for (int i = 0; i < n; ++i)
        {
            mat.m[i][i] = 1;
        }

        return mat;
    }

    static Matrix Random(int n, int from, int to)
    {
        Matrix out(n, n);

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                out.m[i][j] = Rand(from, to);
            }
        }

        return out;
    }

private:
    static void Add(const Matrix& a, const Matrix& b, Matrix& out)
    {
        const int Rows = a.GetRows();
        const int Columns = a.GetColumns();

        for (int i = 0; i < Rows; ++i)
        {
            for (int j = 0; j < Columns; ++j)
            {
                out.m[i][j] = a.m[i][j] + b.m[i][j];
            }
        }
    }

    static void Sub(const Matrix& a, const Matrix& b, Matrix& out)
    {
        const int Rows = a.GetRows();
        const int Columns = a.GetColumns();

        for (int i = 0; i < Rows; ++i)
        {
            for (int j = 0; j < Columns; ++j)
            {
                out.m[i][j] = a.m[i][j] - b.m[i][j];
            }
        }
    }

    static void Mul(const Matrix& a, T k, Matrix& out)
    {
        const int Rows = a.GetRows();
        const int Columns = a.GetColumns();

        for (int i = 0; i < Rows; ++i)
        {
            for (int j = 0; j < Columns; ++j)
            {
                out.m[i][j] = a.m[i][j] * k;
            }
        }
    }

    static void Mod(const Matrix& a, long long k, Matrix& out)
    {
        const int Rows = a.GetRows();
        const int Columns = a.GetColumns();

        for (int i = 0; i < Rows; ++i)
        {
            for (int j = 0; j < Columns; ++j)
            {
                out.m[i][j] = a.m[i][j] % k;
            }
        }
    }

public:
    vector<vector<T>> m;
};

using Mat = Matrix<ll>;

// 분할 정복
Mat PowRecursive(const Mat& base, ll p)
{
    const int N = base.GetRows();

    if (p == 1)
        return base;

    if (p % 2 == 0)
    {
        Mat val = PowRecursive(base, p / 2);
        return Mat::Mul(val, val);
    }
    else
    {
        Mat val = PowRecursive(base, p / 2);
        return Mat::Mul(val, Mat::Mul(val, base));
    }
}

// 캐시 적용
map<ll, Mat> cache;
Mat PowCache(const Mat& base, ll p)
{
    const int N = base.GetRows();

    if (p == 1)
        return base;

    if (cache.find(p) != end(cache))
        return cache[p];

    if (p % 2 == 0)
    {
        Mat val = PowCache(base, p / 2);
        return cache[p] = Mat::Mul(val, val);
    }
    else
    {
        Mat val = PowCache(base, p / 2);
        return cache[p] = Mat::Mul(val, Mat::Mul(val, base));
    }
}


// 반복문
Mat Pow(const Mat& base, ll p)
{
    const int N = base.GetRows();
    Mat ans = Mat::Identity(N);
    Mat a = base;
    while (p > 0)
    {
        if (p % 2 == 1)
        {
            ans = Mat::Mul(ans, a);
        }
        a = Mat::Mul(a, a);
        p /= 2;
    }
    return ans;
}

void Baekjoon()
{
    ll n, b;
    cin >> n >> b;

    Mat mat(n, n);
    Mat::Input(mat);

    Mat out = PowRecursive(Mat::Mod(mat, 1000), b);
    out.Print();
}

int main()
{
    Baekjoon();

    return 0;
}

