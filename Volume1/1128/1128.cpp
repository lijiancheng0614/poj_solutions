#include <iostream>
#include <string>
#include <vector>
using namespace std;
#define N 26
typedef pair<int, int> pii;
typedef vector<bool> vb;
class Solution
{
public:
    vector<string> solve(const vector<string> & a)
    {
        int h = a.size(), w = a[0].length();
        n = 0;
        d.assign(N, -1);
        g.assign(N, vb(N, false));
        vector<pii> lu(N, pii(h, w)), rd(N, pii(0, 0));
        for (int i = 0; i < h; ++i)
            for (int j = 0; j < w; ++j)
            {
                if (a[i][j] == '.')
                    continue;
                int k = a[i][j] - 'A';
                if (d[k] < 0)
                {
                    ++n;
                    d[k] = 0;
                }
                lu[k].first = min(lu[k].first, i);
                lu[k].second = min(lu[k].second, j);
                rd[k].first = max(rd[k].first, i);
                rd[k].second = max(rd[k].second, j);
            }
        for (int i = 0; i < N; ++i)
        {
            if (d[i] < 0)
                continue;
            for (int x = lu[i].first; x <= rd[i].first; ++x)
                for (int y = lu[i].second; y <= rd[i].second; ++y)
                {
                    if (x > lu[i].first && x < rd[i].first && y > lu[i].second)
                        y = rd[i].second;
                    int j = a[x][y] - 'A';
                    if (j != i && !g[i][j])
                    {
                        g[i][j] = true;
                        ++d[j];
                    }
                }
        }
        ans.assign(n, ' ');
        dfs(0);
        return outputs;
    }
private:
    vector<string> outputs;
    vector<vb> g;
    vector<int> d;
    int n;
    string ans;
    void dfs(int k)
    {
        if (k >= n)
        {
            outputs.push_back(ans);
            return;
        }
        for (int i = 0; i < N; ++i)
            if (d[i] == 0)
            {
                ans[k] = i + 'A';
                --d[i];
                for (int j = 0; j < N; ++j)
                    if (g[i][j])
                        --d[j];
                dfs(k + 1);
                for (int j = 0; j < N; ++j)
                    if (g[i][j])
                        ++d[j];
                ++d[i];
            }
    }
};

int main()
{
    int h, w;
    while (cin >> h >> w)
    {
        vector<string> a;
        for (int i = 0; i < h; ++i)
        {
            string line;
            cin >> line;
            a.push_back(line);
        }
        vector<string> outputs = Solution().solve(a);
        for (int i = 0; i < outputs.size(); ++i)
            cout << outputs[i] << endl;
    }
    return 0;
}
