#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
const int dx[] = {0, -1, 0, 1};
const int dy[] = {-1, 0, 1, 0};
class Solution
{
public:
    pii solve(vvi & a)
    {
        n = a.size(), m = a[0].size();
        int tot = 0, s_max = 0;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                if (~a[i][j])
                {
                    s = 0;
                    dfs(i, j, a);
                    s_max = max(s_max, s);
                    ++tot;
                }
        return pii(tot, s_max);
    }
private:
    int n, m, s;
    void dfs(int i, int j, vvi & a)
    {
        ++s;
        int state = a[i][j];
        a[i][j] = -1;
        for (int k = 0; k < 4; ++k)
        {
            if (!(state & 1))
            {
                int x = i + dx[k];
                int y = j + dy[k];
                if (x >= 0 && x < n && y >= 0 && y < m && ~a[x][y])
                    dfs(x, y, a);
            }
            state >>= 1;
        }
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
    pii ans = Solution().solve(a);
    cout << ans.first << endl;
    cout << ans.second << endl;
    return 0;
}
