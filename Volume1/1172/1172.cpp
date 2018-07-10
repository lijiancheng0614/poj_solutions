#include <iostream>
#include <queue>
#include <vector>
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;
class Graph
{
public:
    vi unavoidable, splitting;
    Graph(int n = 50) : n(n)
    {
        a.assign(n, vi());
    }
    void add(int i, int j)
    {
        a[i].push_back(j);
    }
    int solve(int n)
    {
        this->n = n;
        unavoidable.clear();
        splitting.clear();
        for (int i = 1; i < n; ++i)
            if (bfs(i))
            {
                unavoidable.push_back(i);
                if (check(i))
                    splitting.push_back(i);
            }
    }
private:
    vvi a;
    vector<bool> v;
    int n;
    bool bfs(int k)
    {
        v.assign(n + 1, false);
        queue<int> q;
        q.push(0);
        v[0] = v[k] = true;
        while (!q.empty())
        {
            int h = q.front();
            q.pop();
            for (int i = 0; i < a[h].size(); ++i)
            {
                int j = a[h][i];
                if (!v[j])
                {
                    q.push(j);
                    v[j] = true;
                }
            }
        }
        return !v[n - 1];
    }
    bool check(int k)
    {
        for (int x = 0; x <= n; ++x)
            if (!v[x] || x == k)
                for (int i = 0; i < a[x].size(); ++i)
                {
                    int y = a[x][i];
                    if (v[y] && y != k)
                        return false;
                }
        return true;
    }
};

int main()
{
    Graph g;
    int n = 0;
    for (int j = 0; ~j; ++n)
        while (cin >> j && j >= 0)
            g.add(n, j);
    g.solve(n);
    cout << g.unavoidable.size();
    for (int i = 0; i < g.unavoidable.size(); ++i)
        cout << " " << g.unavoidable[i];
    cout << endl;
    cout << g.splitting.size();
    for (int i = 0; i < g.splitting.size(); ++i)
        cout << " " << g.splitting[i];
    cout << endl;
    return 0;
}
