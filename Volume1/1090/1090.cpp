#include <iostream>
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
};
const BigInt TWO(2);
class Solution
{
public:
    BigInt solve(vector<int> & a)
    {
        int n = a.size();
        int s = 0;
        for (int i = 0; i < n; ++i)
            s += a[i];
        BigInt ans, t(1);
        for (int i = 0; i < n; ++i)
        {
            s -= a[i];
            if (s & 1)
                a[i] = 1 - a[i];
            if (a[i])
                ans = ans + t;
            t = t * TWO;
        }
        return ans;
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

int main()
{
    int n;
    cin >> n;
    vector<int> a;
    for (int i = 0; i < n; ++i)
    {
        int x;
        cin >> x;
        a.push_back(x);
    }
    BigInt ans = Solution().solve(a);
    cout << ans << endl;
    return 0;
}
