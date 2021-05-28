#pragma once

#include "Headers.h"
#include "Print.h"
#include "Utility.h"

template<typename T>
struct Vec
{
    Vec() : x(0), y(0) {}
    Vec(int x, int y) : x(x), y(y) {}

public:
    bool operator==(const Vec& other) const
    {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Vec& other) const
    {
        return !(*this == other);
    }

    bool operator<(const Vec& other) const
    {
        if (x == other.x)
        {
            return y < other.y;
        }

        return x < other.x;
    }

    // for greater
    bool operator>(const Vec& other) const
    {
        if (x == other.x)
            return y > other.y;

        return x > other.x;
    }

    Vec operator+(const Vec& other) const
    {
        return Vec(x + other.x, y + other.y);
    }

    Vec operator-(const Vec& other) const
    {
        return Vec(x - other.x, y - other.y);
    }

    // unary minus
    Vec operator- ()
    {
        return Vec(-x, -y);
    }

public:
    T x;
    T y;
};

struct Time
{
    Time() : tm(), milisec(0) {}

    // "08:31", "19:59"
    void ParseHourMinSecMilisec(std::string time)
    {
        Parse(time, "%H:%M:%S.%s");
    }

    // "08:31", "19:59"
    void ParseHourMinSec(std::string time)
    {
        Parse(time, "%H:%M:%S");
    }

    // "08:31", "19:59"
    void ParseHourMin(std::string time)
    {
        Parse(time, "%H:%M");
    }

    // "55:31", "00:59"
    void ParseMinSec(std::string time)
    {
        Parse(time, "%M:%S");
    }

    // time : "2017.10.30 08:31:05.312",    "2017-10-30 08-31-05-312"
    // format : "%Y.%m.%d %H:%M:%S.%s",     "%Y-%m-%d %H-%M-%S-%s"
    void Parse(std::string time, std::string format)
    {
        size_t index = format.find("%s");

        if (index != std::string::npos)
        {
            size_t rindex = time.rfind(format[index - 1]);
            std::string sub = time.substr(rindex + 1, 3);
            milisec = stof(sub);
        }

        std::istringstream ss(time);
        ss >> std::get_time(&tm, format.c_str());
    }

    long long Second() const
    {
        return tm.tm_sec;
    }

    long long Minute() const
    {
        return tm.tm_min;
    }

    long long Hour() const
    {
        return tm.tm_hour;
    }

    long long YearDay() const
    {
        return tm.tm_yday;
    }

    long long MonthDay() const
    {
        return tm.tm_mday;
    }

    long long WeekDay() const
    {
        return tm.tm_wday;
    }

    long long Month() const
    {
        return (long long)tm.tm_mon + (long long)1;
    }

    long long Year() const
    {
        return (long long)tm.tm_year + (long long)1900;
    }

    long long ToKey() const
    {
        long long total = tm.tm_year;
        total *= 12;
        total += tm.tm_mon;
        total *= 32;
        total += tm.tm_mday;
        total *= 24;
        total += tm.tm_hour;
        total *= 60;
        total += tm.tm_min;
        total *= 60;
        total += tm.tm_sec;
        total *= 1000;
        total += milisec;

        return total;
    }

    void FromKey(long long key)
    {
        milisec = key % 1000;
        key /= 1000;
        tm.tm_sec = key % 60;
        key /= 60;
        tm.tm_min = key % 60;
        key /= 60;
        tm.tm_hour = key % 24;
        key /= 24;
        tm.tm_mday = key % 32;
        key /= 32;
        tm.tm_mon = key % 12;
        key /= 12;
        tm.tm_year = key;
    }

    void Print() const
    {
        std::cout << "Key : " << ToKey() << "\tYear : " << Year() << "\tMonth : " << Month() << "\tMonthDay : " << MonthDay() << "\tHour : " << Hour() << "\tMinute : " << Minute() << "\tSecond : " << Second() << "\tMilisec : " << milisec << std::endl;
    }

private:
    std::tm tm;
    int milisec;
};

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
    Matrix(int rows, int columns) : m(rows, std::vector<T>(columns, 0)) {}

    int GetRows() const { return m.size(); }
    int GetColumns() const { return m[0].size(); }

    void Print() const
    {
        using namespace std;
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
        using namespace std;
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

                //out.m[i][k] %= 1000;
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
                out.m[i][j] = Utility::Rand(from, to);
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
    std::vector<std::vector<T>> m;
};


struct Idx
{
    int i, j;
};

struct QueueData
{
    Idx state;
    int cnt;
};

