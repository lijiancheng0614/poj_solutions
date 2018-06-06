#include <iostream>
#include <vector>
using namespace std;
const int oo = 1 << 30;
typedef vector<int> vi;
class Solution
{
public:
    int dp(const vi & a, int m)
    {
        int n = a.size();
        vector<vi> d(n, vi(n, 0));
        for (int i = 0; i < n; ++i)
            for (int j = i; j < n; ++j)
                d[i][j] = get_total(i, j, a);
        vector<vi> f(2, vi(n + 1, oo));
        f[0][0] = 0;
        for (int i = 1; i <= m; ++i)
        {
            f[i & 1].assign(n + 1, oo);
            for (int j = i; j <= n; ++j)
                for (int k = 0; k < j; ++k)
                    f[i & 1][j] = min(f[i & 1][j], f[(i - 1) & 1][k] + d[k][j - 1]);
        }
        return f[m & 1][n];
    }
private:
    int get_total(int i, int j, const vi & a)
    {
        int s = 0;
        for (; i < j; ++i, --j)
            s += a[j] - a[i];
        return s;
    }
};

int main()
{
    int n, m;
    cin >> n >> m;
    vi a(n, 0);
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    cout << Solution().dp(a, m) << endl;
    return 0;
}
