#include <iostream>
#include <string>
#include <vector>
using namespace std;
#define B 10
class BigInt : vector<int>
{
public:
    BigInt(int b = 0)
    {
        while (b >= B)
        {
            push_back(b % B);
            b /= B;
        }
        if (b)
            push_back(b);
    }
    BigInt operator+(const BigInt &b)
    {
        BigInt c = *this;
        c.resize(max(c.size(), b.size()));
        int t = 0;
        for (int i = 0; i < b.size(); ++i)
        {
            c[i] += t + b[i];
            t = c[i] / B;
            c[i] %= B;
        }
        for (int i = b.size(); t && i < c.size(); ++i)
        {
            c[i] += t;
            t = c[i] / B;
            c[i] %= B;
        }
        if (t)
            c.push_back(t);
        return c;
    }
    BigInt operator*(const BigInt &b)
    {
        BigInt c;
        c.assign(size() + b.size() + 1, 0);
        for (int i = 0; i < size(); ++i)
            for (int j = 0; j < b.size(); ++j)
            {
                c[i + j] += (*this)[i] * b[j];
                if (c[i + j] >= B)
                {
                    c[i + j + 1] += c[i + j] / B;
                    c[i + j] %= B;
                }
            }
        while (c.size() > 1 && !c.back())
            c.pop_back();
        return c;
    }
    BigInt operator^(int b)
    {
        if (b == 0)
            return 1;
        if (b == 2)
            return (*this) * (*this);
        if (b & 1)
            return (*this) * ((*this) ^ (b - 1));
        return ((*this) ^ (b >> 1)) ^ 2;
    }
    void print(int p)
    {
        int i = size();
        if (!i || (i == 1 && back() == 0))
        {

        }
        else if (p > i)
        {
            cout << ".";
            for (i = p; i > size(); --i)
                cout << "0";
            for (i = 0; i < size(); ++i)
                if ((*this)[i])
                    break;
            for (int j = size() - 1; j >= i; --j)
                cout << (*this)[j];
        }
        else
        {
            for (--i; i >= p; --i)
                cout << (*this)[i];
            for (i = 0; i < p; ++i)
                if ((*this)[i])
                    break;
            if (i < p)
                cout << ".";
            for (int j = p - 1; j >= i; --j)
                cout << (*this)[j];
        }
        cout << endl;
    }
};

void solve(string s, int n)
{
    int r = 0, p = 0;
    for (int i = 0; i < s.length(); ++i)
    {
        if (s[i] == '.')
            p = 5 - i;
        else
            r = r * 10 + s[i] - '0';
    }
    BigInt a(r);
    a = a ^ n;
    a.print(p * n);
}

int main()
{
    string s;
    int n;
    while (cin >> s >> n)
    {
        solve(s, n);
    }
    return 0;
}
