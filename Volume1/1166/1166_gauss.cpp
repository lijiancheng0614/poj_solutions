#include <iostream>
#include <vector>
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;
const int p = 4;
const int moves[][6] =
{
    {0, 1, 3, 4, -1},
    {0, 1, 2, -1},
    {1, 2, 4, 5, -1},
    {0, 3, 6, -1},
    {1, 3, 4, 5, 7, -1},
    {2, 5, 8, -1},
    {3, 4, 6, 7, -1},
    {6, 7, 8, -1},
    {4, 5, 7, 8, -1}
};
class Solution
{
public:
    vi solve(vvi & a)
    {
        vi ans;
        gauss(a);
        for (int i = 0; i < x.size(); ++i)
            for (int j = 0; j < x[i]; ++j)
                ans.push_back(i + 1);
        return ans;
    }
private:
    vi x;
    void gauss(vvi & a)
    {
        int n = a.size(), m = a[0].size() - 1;
        x.assign(n, 0);
        int r = 0, c = 0;
        while (r < n && c < m)
        {
            int i;
            for (i = r; i < n; ++i)
                if (a[i][c])
                    break;
            if (i >= n)
            {
                ++c;
                continue;
            }
            if (i != r)
                for (int j = c; j < m + 1; ++j)
                    swap(a[i][j], a[r][j]);
            for (i = r + 1; i < n; ++i)
                if (a[i][c])
                {
                    int x1 = a[i][c], x2 = a[r][c];
                    for (int j = c; j < m + 1; ++j)
                        a[i][j] = ((a[i][j] * x2 - a[r][j] * x1) % p + p) % p;
                }
            ++r;
        }
        for (int i = r - 1; i >= 0; --i)
        {
            int t = a[i][m];
            for (int j = i + 1; j < m; ++j)
                t = ((t - a[i][j] * x[j]) % p + p) % p;
            while (t % a[i][i])
                t += p;
            x[i] = (t / a[i][i] % p + p) % p;
        }
    }
};

int main()
{
    vvi a(9, vi(10, 0));
    for (int i = 0; i < 9; ++i)
    {
        cin >> a[i][9];
        a[i][9] = (4 - a[i][9]) % 4;
        for (int j = 0; ~moves[i][j]; ++j)
            a[moves[i][j]][i] = 1;
    }
    vi ans = Solution().solve(a);
    for (int i = 0; i < ans.size(); ++i)
        cout << ans[i] << " ";
    return 0;
}
