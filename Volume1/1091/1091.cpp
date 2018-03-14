#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;
#define B 10000
#define L 4
class BigInt : vector<int>
{
    friend ostream& operator<<(ostream & os, const BigInt & b);
public:
    BigInt(int b = 0)
    {
        if (!b)
        {
            push_back(b);
            return;
        }
        while (b >= B)
        {
            push_back(b % B);
            b /= B;
        }
        if (b)
            push_back(b);
    }
    bool operator!=(const BigInt & b)
    {
        if (size() != b.size())
            return 1;
        for (int i = size() - 1; i >= 0; --i)
            if ((*this)[i] != b[i])
                return 1;
        return 0;
    }
    bool operator==(const BigInt & b)
    {
        return !((*this) != b);
    }
    BigInt operator+(const BigInt & b) const
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
    BigInt operator-(const BigInt & b) const
    {
        BigInt c = *this;
        for (int i = 0; i < b.size(); ++i)
        {
            c[i] -= b[i];
            if (c[i] < 0)
            {
                --c[i + 1];
                c[i] += B;
            }
        }
        for (int i = b.size(); i < size() && c[i] < 0; ++i)
        {
            --c[i + 1];
            c[i] += B;
        }
        while (c.size() > 1 && !c.back())
            c.pop_back();
        return c;
    }
    BigInt operator*(const BigInt & b) const
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
    BigInt operator^(int b) const
    {
        if (b == 0)
            return 1;
        if (b == 2)
            return (*this) * (*this);
        if (b & 1)
            return (*this) * ((*this) ^ (b - 1));
        return ((*this) ^ (b >> 1)) ^ 2;
    }
    BigInt operator+=(const BigInt & b)
    {
        *this = *this + b;
        return *this;
    }
    BigInt operator-=(const BigInt & b)
    {
        *this = *this - b;
        return *this;
    }
};
ostream& operator<<(ostream & os, const BigInt & b)
{
    int n = b.size() - 1;
    os << b[n];
    for (int i = n - 1; i >= 0; --i)
    {
        os.width(L);
        os.fill('0');
        os << b[i];
    }
    return os;
}
const BigInt ONE(1);
class Solution
{
public:
    BigInt solve(int n, int m)
    {
        BigInt ans = BigInt(m) ^ n;
        this->n = n;
        this->m = m;
        for (int i = 2; i * i <= m; ++i)
            if (m % i == 0)
            {
                p.push_back(i);
                while (m % i == 0)
                    m /= i;
            }
        if (m > 1)
            p.push_back(m);
        for (tot = 1; tot <= p.size(); ++tot)
        {
            cnt = 0;
            dfs(0, 0, 1);
            if (tot & 1)
                ans -= cnt;
            else
                ans += cnt;
        }
        return ans;
    }
private:
    vector<int> p;
    BigInt cnt;
    int n, m, tot;
    void dfs(int k, int i, int s)
    {
        if (k == tot)
        {
            cnt += BigInt(m / s) ^ n;
            return;
        }
        for (; i < p.size(); ++i)
            dfs(k + 1, i + 1, s * p[i]);
    }
};

int main()
{
    int n, m;
    cin >> n >> m;
    BigInt ans = Solution().solve(n, m);
    cout << ans << endl;
    return 0;
}
