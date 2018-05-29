#include <iostream>
#include <vector>
using namespace std;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vpii;
const int oo = 1 << 30;
class Graph
{
public:
    Graph(int n, int m) : n(n), m(m)
    {
        a.assign(n, vpii());
    }
    void add(int i, int j, int k)
    {
        a[i].push_back(pii(j, k));
    }
    int solve(const vi & w)
    {
        dp(0, w);
        for (int i = m; i; --i)
            if (f[i] >= 0)
                return i;
    }
private:
    vector<vpii> a;
    vi f;
    int n, m;
    int dp(int k, const vi & w)
    {
        f.assign(m + 1, -oo);
        vi g(m + 1, -oo);
        f[0] = g[0] = 0;
        int s = 0;
        for (int i = 0; i < a[k].size(); ++i)
        {
            int j = a[k][i].first;
            int t = dp(j, w);
            for (int x = s; x >= 0; --x)
                for (int y = 1; y <= t && x + y <= m; ++y)
                    g[x + y] = max(g[x + y], g[x] + f[y] - a[k][i].second);
            s += t;
        }
        if (!a[k].size())
        {
            f[1] = w[k];
            return 1;
        }
        for (int i = s; i; --i)
            f[i] = g[i];
        return s;
    }
};

int main()
{
    int n, m;
    cin >> n >> m;
    Graph g(n, m);
    for (int i = 0; i < n - m; ++i)
    {
        int k;
        cin >> k;
        while (k--)
        {
            int j, c;
            cin >> j >> c;
            g.add(i, j - 1, c);
        }
    }
    vi w(n, 0);
    for (int i = n - m; i < n; ++i)
        cin >> w[i];
    cout << g.solve(w) << endl;
    return 0;
}
