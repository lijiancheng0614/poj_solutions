#include <iostream>
#include <string>
#include <vector>
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;
class BC
{
public:
    BC(int n, int k, int m) : n(n), k(k), m(m)
    {
        f.assign(k + 1, vi(n + 1, 0));
        f[0][0] = 1;
        for (int i = 0; i < k; ++i)
            for (int j = 0; j < n; ++j)
                if (f[i][j])
                    for (int l = 1; l <= m && j + l <= n; ++l)
                        f[i + 1][j + l] += f[i][j];
    }
    int get_count()
    {
        return f[k][n];
    }
    int get_rank(const string & a)
    {
        int s = 0;
        int kk = 1;
        for (int ii = 0, i = 1; i < a.length(); ++i)
            if (a[i] != a[i - 1])
            {
                if (a[i] == '0')
                    for (int j = ii + 1; j < i; ++j)
                        s += f[k - kk][n - j];
                else
                    for (int j = min(n - 1, ii + m); j > i; --j)
                        s += f[k - kk][n - j];
                ++kk;
                ii = i;
            }
        return s;
    }
private:
    vvi f;
    int n, k, m;
};

int main()
{
    int n, k, m;
    cin >> n >> k >> m;
    BC bc(n, k, m);
    cout << bc.get_count() << endl;
    int t;
    cin >> t;
    while (t--)
    {
        string a;
        cin >> a;
        cout << bc.get_rank(a) << endl;
    }
    return 0;
}
