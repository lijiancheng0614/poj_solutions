#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<double> vd;
typedef vector<vd> vvd;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef pair<int, int> pii;
typedef vector<pii> vpii;
typedef vector<vpii> vvpii;
const int oo = 1 << 30;
const int dx[] = { -1, 0, 1, 0};
const int dy[] = {0, -1, 0, 1};
class Solution
{
public:
    void solve(vvd & outputs, const vector<string> & a, const map<string, int> & load)
    {
        n = a.size();
        m = a[0].length();
        pos.assign(15, pii());
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                if (a[i][j] >= 'A' && a[i][j] <= 'O')
                    pos[a[i][j] - 'A'] = pii(i, j);
        outputs.assign(n, vd(m, 0));
        pre.assign(n, vpii(m, pii()));
        for (map<string, int>::const_iterator it = load.begin(); it != load.end(); ++it)
        {
            string route = it->first;
            int l = it->second;
            x0 = pos[route[0] - 'A'].first, y0 = pos[route[0] - 'A'].second;
            x1 = pos[route[1] - 'A'].first, y1 = pos[route[1] - 'A'].second;
            f.assign(n, vi(m, 0));
            v.assign(n, vb(m, false));
            v[x0][y0] = true;
            tot = 0;
            len_min = oo;
            dfs(x0, y0, 0, a);
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < m; ++j)
                    outputs[i][j] += double(f[i][j]) / tot * l;
        }
    }
private:
    vpii pos;
    vvpii pre;
    vvi f;
    vvb v;
    int n, m, tot, len_min;
    int x0, y0, x1, y1;
    void dfs(int x, int y, int len, const vector<string> & a)
    {
        if (x == x1 && y == y1)
        {
            if (len > len_min)
                return;
            else if (len < len_min)
            {
                f.assign(n, vi(m, 0));
                tot = 1;
            }
            else
                ++tot;
            len_min = len;
            for (int xx = pre[x][y].first, yy = pre[x][y].second; xx != x0 || yy != y0;
                    xx = pre[x][y].first, yy = pre[x][y].second)
            {
                ++f[xx][yy];
                x = xx;
                y = yy;
            }
            return;
        }
        if (len >= len_min)
            return;
        for (int k = 0; k < 4; ++k)
        {
            int xx = x + dx[k];
            int yy = y + dy[k];
            if (xx >= 0 && xx < n && yy >= 0 && yy < m && !v[xx][yy] &&
                    (a[xx][yy] == '.' || (xx == x1 && yy == y1)))
            {
                v[xx][yy] = true;
                pre[xx][yy] = pii(x, y);
                dfs(xx, yy, len + 1, a);
                v[xx][yy] = false;
            }
        }
    }
};

int main()
{
    int n, m;
    cin >> m >> n;
    vector<string> a(n, "");
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    map<string, int> load;
    string route;
    int l;
    while (cin >> route >> l && route != "XX")
    {
        if (route[0] > route[1])
            swap(route[0], route[1]);
        load[route] += l;
    }
    vvd outputs;
    Solution().solve(outputs, a, load);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
            cout << setw(7) << fixed << setprecision(2) << outputs[i][j];
        cout << endl;
    }
    return 0;
}
