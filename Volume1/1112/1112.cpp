#include <iostream>
#include <vector>
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;
typedef vector<bool> vb;
typedef vector<vb> vvb;
class Graph
{
public:
    Graph(int n) : n(n)
    {
        g.assign(n, vi());
    }
    void add(int i, int j)
    {
        g[i].push_back(j);
        g[j].push_back(i);
    }
    vvvi get_components()
    {
        v.assign(n, 2);
        components.clear();
        n_components = 0;
        for (int i = 0; i < n; ++i)
            if (v[i] == 2)
            {
                components.push_back(vvi(2, vi()));
                v[i] = 0;
                if (!dfs(i))
                    return vvvi();
                ++n_components;
            }
        return components;
    }
private:
    vvi g;
    vvvi components;
    vi v;
    int n, n_components;
    bool dfs(int k)
    {
        components[n_components][v[k]].push_back(k);
        for (int i = 0; i < g[k].size(); ++i)
        {
            int j = g[k][i];
            if (v[j] == 2)
            {
                v[j] = !v[k];
                if (!dfs(j))
                    return false;
            }
            else if (v[j] == v[k])
                return false;
        }
        return true;
    }
};
class Solution
{
public:
    vvi solve(const vvb & a)
    {
        int n = a.size();
        Graph graph(n);
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j)
                if (!a[i][j] || !a[j][i])
                    graph.add(i, j);
        vvvi components = graph.get_components();
        if (components.size() == 0)
            return vvi();
        return dp(components, n);
    }
private:
    vvi dp(const vvvi & components, int n)
    {
        int n_components = components.size();
        int n2 = n / 2;
        vvb f(n_components + 1, vb(n2 + 1, false));
        vvi g(n_components + 1, vi(n2 + 1, 0));
        f[0][0] = true;
        for (int i = 0; i < components.size(); ++i)
            for (int j = 0; j <= n2; ++j)
                for (int k = 0; k < 2; ++k)
                {
                    int jj = j - components[i][k].size();
                    if (jj >= 0 && f[i][jj])
                    {
                        f[i + 1][j] = true;
                        g[i + 1][j] = k;
                    }
                }
        int j;
        for (j = n2; j; --j)
            if (f[n_components][j])
                break;
        if (!j)
            return vvi();
        vb v(n, false);
        for (int i = n_components - 1; i >= 0; --i)
        {
            int k = g[i + 1][j];
            j -= components[i][k].size();
            for (int ii = 0; ii < components[i][k].size(); ++ii)
                v[components[i][k][ii]] = true;
        }
        vvi groups(2, vi());
        for (int i = 0; i < n; ++i)
            groups[v[i]].push_back(i + 1);
        return groups;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    vvb a(n, vb(n, false));
    for (int i = 0; i < n; ++i)
    {
        int j;
        while (cin >> j && j)
            a[i][j - 1] = true;
    }
    vvi groups = Solution().solve(a);
    if (groups.size() == 0)
        cout << "No solution" << endl;
    else
        for (int i = 0; i < groups.size(); ++i)
        {
            cout << groups[i].size();
            for (int j = 0; j < groups[i].size(); ++j)
                cout << " " << groups[i][j];
            cout << endl;
        }
    return 0;
}
