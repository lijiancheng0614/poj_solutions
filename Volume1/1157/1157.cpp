#include <iostream>
#include <vector>
using namespace std;
const int oo = 1 << 30;
typedef vector<int> vi;
typedef vector<vi> vvi;
class Solution
{
public:
    int solve(const vvi & a)
    {
        int n = a.size(), m = a[0].size();
        vvi f(n + 1, vi(m + 1, 0));
        for (int i = 1; i <= n; ++i)
            for (int j = 0; j < i; ++j)
                f[i][j] = -oo;
        for (int j = 1; j <= m; ++j)
            for (int i = 1; i <= j && i <= n; ++i)
                f[i][j] = max(f[i][j - 1], f[i - 1][j - 1] + a[i - 1][j - 1]);
        return f[n][m];
    }
};

int main()
{
    int n, m;
    cin >> n >> m;
    vvi a(n, vi(m, 0));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> a[i][j];
    cout << Solution().solve(a) << endl;
    return 0;
}
