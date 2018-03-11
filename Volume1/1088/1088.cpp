#include <iostream>
#include <vector>
using namespace std;
typedef vector<int> vi;
const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, -1, 0, 1};
class Solution
{
public:
    int solve(const vector<vi> & a)
    {
        n = a.size();
        m = a[0].size();
        f.assign(n, vi(m, 0));
        int ans = 0;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                ans = max(ans, dp(a, i, j));
        return ans;
    }
private:
    vector<vi> f;
    int n, m;
    int dp(const vector<vi> & a, int i, int j)
    {
        if (f[i][j] > 0)
            return f[i][j];
        f[i][j] = 1;
        for (int k = 0; k < 4; ++k)
        {
            int x = i + dx[k];
            int y = j + dy[k];
            if (x >= 0 && x < n && y >= 0 && y < m && a[x][y] < a[i][j])
                f[i][j] = max(f[i][j], dp(a, x, y) + 1);
        }
        return f[i][j];
    }
};

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vi> a(n, vi(m, 0));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> a[i][j];
    cout << Solution().solve(a) << endl;
    return 0;
}
