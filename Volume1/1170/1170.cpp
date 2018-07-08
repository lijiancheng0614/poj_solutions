#include <iostream>
#include <map>
#include <vector>
using namespace std;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vpii;
class Solution
{
public:
    int solve(const vpii & a, const vi & p, int status, int s)
    {
        vi f(status + 1, s);
        f[status] = s;
        f[0] = 0;
        for (int i = 0; i < a.size(); ++i)
            for (int j = a[i].first; j <= status; ++j)
                f[j] = min(f[j], f[j - a[i].first] + a[i].second);
        for (int i = 0; i <= status; ++i)
            f[status] = min(f[status], f[i] + get_p(status - i, p));
        return f[status];
    }
private:
    inline int get_p(int status, const vi & p)
    {
        int s = 0;
        for (int i = 0; status; ++i, status /= 6)
            s += (status % 6) * p[i];
        return s;
    }
};

int main()
{
    map<int, int> h;
    int n;
    cin >> n;
    vi p(n, 0);
    int status = 0, pow6 = 1, s = 0;
    for (int i = 0; i < n; ++i)
    {
        int c, k;
        cin >> c >> k >> p[i];
        status += pow6 * k;
        s += p[i] * k;
        h[c] = pow6;
        pow6 *= 6;
    }
    cin >> n;
    vpii a(n, pii(0, 0));
    for (int i = 0; i < n; ++i)
    {
        int m;
        cin >> m;
        while (m--)
        {
            int c, k;
            cin >> c >> k;
            a[i].first += k * h[c];
        }
        cin >> a[i].second;
    }
    cout << Solution().solve(a, p, status, s) << endl;
    return 0;
}
