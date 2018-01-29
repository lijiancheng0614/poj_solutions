#include <iostream>
#include <vector>
#include <queue>
using namespace std;
typedef pair<int, int> pii;
typedef vector<pii> vpii;
class Graph
{
public:
    Graph(int n) : n(n)
    {
        a.assign(n, pii());
        g.assign(n, vpii());
    }
    void addPoint(int i, int x, int y)
    {
        a[i] = pii(x, y);
    }
    void add(int i, int j, int k)
    {
        g[i].push_back(pii(j, k));
    }
    int solve(int m)
    {
        int ans = a[0].first;
        for (int i = 0; i < n; ++i)
        {
            int x = a[i].second;
            int y = a[i].second + m;
            if (x <= a[0].second && y >= a[0].second)
                spfa(x, y, ans);
        }
        return ans;
    }
private:
    vector<vpii> g;
    vector<pii> a;
    int n;
    void spfa(int x, int y, int & ans)
    {
        queue<int> q;
        vector<bool> v(n, false);
        vector<int> d(n, ans);
        q.push(0);
        v[0] = true;
        d[0] = 0;
        while (!q.empty())
        {
            int h = q.front();
            q.pop();
            for (int i = 0; i < g[h].size(); ++i)
            {
                int j = g[h][i].first;
                if (a[j].second < x || a[j].second > y)
                    continue;
                if (d[h] + g[h][i].second < d[j])
                {
                    d[j] = d[h] + g[h][i].second;
                    if (!v[j])
                    {
                        q.push(j);
                        v[j] = true;
                    }
                }
            }
            v[h] = false;
        }
        for (int i = 1; i < n; ++i)
            ans = min(ans, d[i] + a[i].first);
    }
};

int main()
{
    int m, n;
    cin >> m >> n;
    Graph g(n);
    for (int i = 0; i < n; ++i)
    {
        int x, y, s;
        cin >> x >> y >> s;
        g.addPoint(i, x, y);
        while (s--)
        {
            int j, k;
            cin >> j >> k;
            g.add(i, j - 1, k);
        }
    }
    cout << g.solve(m) << endl;
    return 0;
}
