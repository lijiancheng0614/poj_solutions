#include <iostream>
#include <vector>
#include <string>
using namespace std;
typedef vector<bool> vb;
typedef vector<vb> vvb;
const int dx[] = {-1, 1, 0, 0, -1, -1, 1, 1};
const int dy[] = {0, 0, -1, 1, -1, 1, -1, 1};
class Solution
{
public:
    int solve(const vvb & a, int x, int y)
    {
        int n = a.size(), m = a[0].size();
        v.assign(n, vb(m, false));
        tot = 0;
        dfs(a, x, y);
        return tot;
    }
private:
    vvb v;
    int tot;
    void dfs(const vvb & a, int x, int y)
    {
        v[x][y] = true;
        for (int k = 0; k < 8; ++k)
        {
            int i = x + dx[k];
            int j = y + dy[k];
            if (!a[i][j])
                tot += k < 4;
            else if (!v[i][j])
                dfs(a, i, j);
        }
    }
};

int main()
{
    int n, m, x, y;
    while (cin >> n >> m >> x >> y && n)
    {
        ++n, ++m;
        vvb a(n + 1, vb(m + 1, false));
        for (int i = 1; i < n; ++i)
        {
            string s;
            cin >> s;
            for (int j = 1; j < m; ++j)
                a[i][j] = s[j - 1] == 'X';
        }
        cout << Solution().solve(a, x, y) << endl;
    }
    return 0;
}
