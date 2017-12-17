#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
typedef pair<int, int> pii;
typedef vector<int> vi;

class Graph
{
public:
    Graph(int n, int m) : n(n), m(m)
    {
        g.assign(n, vi());
    }
    void add(int i, int j)
    {
        g[i].push_back(j);
    }
    vi max_match()
    {
        l.assign(m, -1);
        r.assign(n, -1);
        for (int i = 0; i < n; ++i)
        {
            T.assign(m, false);
            find(i);
        }
        return r;
    }
private:
    vector<vi> g;
    vi l, r;
    vector<bool> T;
    int n, m;
    bool find(int k)
    {
        for (int i = 0; i < g[k].size(); ++i)
        {
            int j = g[k][i];
            if (!T[j])
            {
                T[j] = true;
                if (l[j] < 0 || find(l[j]))
                {
                    l[j] = k;
                    r[k] = j;
                    return true;
                }
            }
        }
        return false;
    }
};

class Solution
{
public:
    vector<pii> solve(vector<pii> & a, vector<pii> & b)
    {
        int n = a.size();
        int m = b.size();
        Graph g(n - 1, m);
        for (int i = 0; i < n - 1; ++i)
        {
            double dis = get_distance(a[i], a[i + 1]);
            for (int j = 0; j < m; ++j)
            {
                double dis2 = get_distance(a[i], b[j]) + get_distance(a[i + 1], b[j]);
                if (dis2 <= dis * 2)
                {
                    g.add(i, j);
                }
            }
        }
        vi r = g.max_match();
        vector<pii> ans;
        for (int i = 0; i < n - 1; ++i)
        {
            ans.push_back(a[i]);
            if (r[i] >= 0)
                ans.push_back(b[r[i]]);
        }
        ans.push_back(a[n - 1]);
        return ans;
    }
private:
    double get_distance(pii & a, pii & b)
    {
        return sqrt(sqr(a.first - b.first) + sqr(a.second - b.second));
    }
    inline int sqr(int x)
    {
        return x * x;
    }
};

int main()
{
    vector<pii> a, b;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i)
    {
        int x, y;
        cin >> x >> y;
        a.push_back(pii(x, y));
    }
    for (int i = 0; i < m; ++i)
    {
        int x, y;
        cin >> x >> y;
        b.push_back(pii(x, y));
    }
    vector<pii> ans = Solution().solve(a, b);
    cout << ans.size() << endl;
    n = ans.size() - 1;
    for (int i = 0; i < n; ++i)
        cout << ans[i].first << " " << ans[i].second << " ";
    cout << ans[n].first << " " << ans[n].second << endl;
    return 0;
}
