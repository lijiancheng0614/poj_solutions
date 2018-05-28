#include <iostream>
#include <vector>
#include <string>
using namespace std;
typedef vector<string> vs;
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};
class Solution
{
public:
    int solve(const vs & a)
    {
        n = a.size(), m = a[0].length();
        v.assign(26, false);
        v[a[0][0] - 'A'] = true;
        ans = 1;
        dfs(a, 0, 0, 1);
        return ans;
    }
private:
    int n, m, ans;
    vector<bool> v;
    void dfs(const vs & a, int i, int j, int s)
    {
        ans = max(ans, s);
        for (int k = 0; k < 4; ++k)
        {
            int x = i + dx[k];
            int y = j + dy[k];
            if (x >= 0 && x < n && y >= 0 && y < m && !v[a[x][y] - 'A'])
            {
                v[a[x][y] - 'A'] = true;
                dfs(a, x, y, s + 1);
                v[a[x][y] - 'A'] = false;
            }
        }
    }
};

int main()
{
    int n, m;
    cin >> n >> m;
    vs a;
    while (n--)
    {
        string s;
        cin >> s;
        a.push_back(s);
    }
    cout << Solution().solve(a) << endl;
    return 0;
}
