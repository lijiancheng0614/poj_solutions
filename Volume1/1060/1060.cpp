#include <iostream>
#include <vector>
using namespace std;
class Polynomial : vector<int>
{
    friend istream& operator>>(istream &is, Polynomial &p);
    friend ostream& operator<<(ostream &os, Polynomial &p);
public:
    Polynomial & operator-=(const Polynomial &b)
    {
        int d = size() - b.size();
        for (int i = 0; i < b.size(); ++i)
            (*this)[i + d] ^= b[i];
        while (size() > 1 && !(*this).back())
            this->pop_back();
        return *this;
    }
    Polynomial operator*(const Polynomial &b)
    {
        Polynomial c;
        c.assign(size() + b.size() - 1, 0);
        for (int i = 0; i < size(); ++i)
            for (int j = 0; j < b.size(); ++j)
                c[i + j] ^= (*this)[i] & b[j];
        return c;
    }
    bool operator>=(const Polynomial &b)
    {
        if (size() > b.size())
            return true;
        if (size() < b.size())
            return false;
        for (int i = size() - 1; i >= 0; --i)
            if ((*this)[i] && !b[i])
                return true;
            else if (!(*this)[i] && b[i])
                return false;
        return true;
    }
    Polynomial operator%(const Polynomial &b)
    {
        Polynomial c = *this;
        while (c >= b)
            c -= b;
        return c;
    }
};

istream& operator>>(istream &is, Polynomial &p)
{
    p.clear();
    int n;
    is >> n;
    p.assign(n, 0);
    for (int i = 0; i < n; ++i)
        is >> p[n - 1 - i];
    return is;
}

ostream& operator<<(ostream &os, Polynomial &p)
{
    int n = p.size();
    os << n;
    for (int i = n - 1; i >= 0; --i)
        os << " " << p[i];
    return os;
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        Polynomial p[3];
        for (int k = 0; k < 3; ++k)
            cin >> p[k];
        p[0] = (p[0] * p[1]) % p[2];
        cout << p[0] << endl;
    }
    return 0;
}
