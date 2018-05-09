#include <iostream>
#include <vector>
using namespace std;
typedef vector<int> vi;
class Graph
{
public:
    bool flag1, flag2;
    Graph(int n)
    {
        a.assign(n, vi());
        v.assign(n, false);
        v2.assign(n, false);
        flag1 = flag2 = false;
    }
    void add(int i, int j)
    {
        a[i].push_back(j);
    }
    void clear(int n)
    {
        a.assign(n, vi());
    }
    void dfs(int k)
    {
        v[k] = true;
        for (int i = 0; i < a[k].size(); ++i)
        {
            int j = a[k][i];
            if (!v[j])
                dfs(j);
        }
    }
    void dfs2(int k, int start)
    {
        if (v[k])
        {
            flag1 = true;
            return;
        }
        v2[k] = true;
        for (int i = 0; i < a[k].size(); ++i)
        {
            int j = a[k][i];
            if (j == start)
                flag2 = true;
            if (!v2[j])
                dfs2(j, start);
        }
    }
private:
    vector<vi> a;
    vector<bool> v, v2;
};

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, x, y;
        cin >> n >> x >> y;
        Graph g(n);
        int i, j;
        while (cin >> i >> j && ~i)
            g.add(i - 1, j - 1);
        g.dfs(x - 1);
        g.clear(n);
        while (cin >> i >> j && ~i)
            g.add(i - 1, j - 1);
        g.dfs2(y - 1, y - 1);
        cout << (g.flag1 ? "Y" : "N") << " " << (g.flag2 ? "Y" : "N") << endl;
    }
    return 0;
}
