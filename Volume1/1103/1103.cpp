#include <iostream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};
typedef vector<bool> vb;
class Solution
{
public:
    string solve(const vector<vb> & a)
    {
        n = a.size(), m = a[0].size();
        v.assign(n, vb(m, false));
        v[0][0] = true;
        dfs(a, 0, 0);
        int count = 0, longest = 0;
        for (int i = 1; i < n; ++i)
            for (int j = 1; j < m; ++j)
                if (!v[i][j] && !a[i][j])
                {
                    ++count;
                    v[i][j] = true;
                    tot = get_value(i, j);
                    dfs(a, i, j);
                    longest = max(longest, tot);
                }
        if (count)
            return to_string(count) + " Cycles; the longest has length " +
                   to_string(longest / 2) + ".";
        return "There are no cycles.";
    }
private:
    int n, m, tot;
    vector<vb> v;
    inline string to_string(int n)
    {
        stringstream ss;
        ss << n;
        return ss.str();
    }
    inline bool get_value(int i, int j)
    {
        return ((i - 1) % 3 + (j - 1) % 3) & 1;
    }
    void dfs(const vector<vb> & a, int i, int j)
    {
        for (int k = 0; k < 4; ++k)
        {
            int x = i + dx[k];
            int y = j + dy[k];
            if (x >= 0 && x < n && y >= 0 && y < m && !v[x][y] && !a[x][y])
            {
                tot += get_value(x, y);
                v[x][y] = true;
                dfs(a, x, y);
            }
        }
    }
};

int main()
{
    int t = 0, n, m;
    while (cin >> m >> n && n)
    {
        vector<vb> a(n * 3 + 2, vb(m * 3 + 2, false));
        for (int i = 1; i <= n; ++i)
        {
            string s;
            cin >> s;
            int x = i * 3 - 1;
            for (int j = 1; j <= m; ++j)
            {
                int y = j * 3 - 1;
                a[x][y] = true;
                if (s[j - 1] == '/')
                    a[x - 1][y + 1] = a[x + 1][y - 1] = true;
                else
                    a[x - 1][y - 1] = a[x + 1][y + 1] = true;
            }
        }
        cout << "Maze #" << ++t << ":" << endl;
        cout << Solution().solve(a) << endl;
        cout << endl;
    }
    return 0;
}
