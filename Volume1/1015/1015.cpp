#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> vii;
typedef vector<vii> viii;

class Solution
{
public:
    vi solve(int n, int m, vector<pii> a, int &s1, int &s2)
    {
        int diff_max = m * 20;
        vii f(m + 1, vi(2 * diff_max + 1, -1));
        viii path(m + 1, vii(2 * diff_max + 1, vi()));
        f[0][diff_max] = 0;
        for (int k = 0; k < n; ++k)
        {
            int diff = a[k].first - a[k].second;
            int sum = a[k].first + a[k].second;
            for (int i = m; i; --i)
                for (int j = 0; j <= 2 * diff_max; ++j)
                    if (j - diff >= 0 && j - diff <= 2 * diff_max &&
                        f[i - 1][j - diff] >= 0 && f[i - 1][j - diff] + sum > f[i][j])
                    {
                        f[i][j] = f[i - 1][j - diff] + sum;
                        path[i][j] = path[i - 1][j - diff];
                        path[i][j].push_back(k);
                    }
        }
        int diff = 0;
        while (f[m][diff_max + diff] < 0 && f[m][diff_max - diff] < 0)
            ++diff;
        if (f[m][diff_max - diff] > f[m][diff_max + diff])
            diff = -diff;
        s1 = (f[m][diff_max + diff] + diff) / 2;
        s2 = (f[m][diff_max + diff] - diff) / 2;
        return path[m][diff_max + diff];
    }
};

int main()
{
    int t = 0;
    int n, m;
    while (cin >> n >> m && n + m > 0)
    {
        vector<pii> a;
        for (int i = 0; i < n; ++i)
        {
            int x, y;
            cin >> x >> y;
            a.push_back(pii(x, y));
        }
        cout << "Jury #" << ++t << endl;
        int s1, s2;
        vi ans = Solution().solve(n, m, a, s1, s2);
        cout << "Best jury has value " << s1 << " for prosecution and value " <<
            s2 << " for defence:" << endl;
        for (int i = 0; i < m; ++i)
            cout << " " << ans[i] + 1;
        cout << endl << endl;
    }
    return 0;
}
