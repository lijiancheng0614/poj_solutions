#include <iostream>
#include <vector>
#include <queue>
using namespace std;
const int oo = 1 << 20;
typedef pair<int, int> pii;
typedef vector<pii> vpii;
typedef vector<vpii> vvpii;
class Node
{
public:
    int rc, tb, tp;
};
class Graph
{
public:
    vector<int> d;
    Graph(int n) : n(n)
    {
        a.assign(n, vpii());
    }
    void add(int i, int j, int k)
    {
        a[i].push_back(pii(j, k));
    }
    int spfa(int x, int y, const vector<Node> & nodes)
    {
        queue<int> q;
        vector<bool> v(n, false);
        d.assign(n, oo);
        q.push(x);
        v[x] = true;
        d[x] = 0;
        while (!q.empty())
        {
            int h = q.front();
            q.pop();
            for (int i = 0; i < a[h].size(); ++i)
            {
                int j = a[h][i].first;
                int t = get_wait_time(d[h], nodes[h], nodes[j]);
                if (~t && d[h] + t + a[h][i].second < d[j])
                {
                    d[j] = d[h] + t + a[h][i].second;
                    if (!v[j])
                    {
                        q.push(j);
                        v[j] = true;
                    }
                }
            }
            v[h] = false;
        }
        return d[y] == oo ? 0 : d[y];
    }
private:
    vvpii a;
    int n;
    bool get_color(int t, const Node & node, int & t_next)
    {
        int tot = node.tb + node.tp;
        if ((node.rc + t) % tot < node.tb)
        {
            t_next = node.tb - (node.rc + t) % tot;
            return false;
        }
        t_next = tot - (node.rc + t) % tot;
        return true;
    }
    int get_wait_time(int t, const Node & i, const Node & j)
    {
        int t1, t2;
        bool c1 = get_color(t, i, t1);
        bool c2 = get_color(t, j, t2);
        if (c1 == c2)
            return 0;
        if (t1 != t2)
            return min(t1, t2);
        if (c1)
        {
            if (i.tb < j.tp)
                return t1 + i.tb;
            if (i.tb > j.tp)
                return t1 + j.tp;
            return -1;
        }
        if (i.tp < j.tb)
            return t1 + i.tp;
        if (i.tp > j.tb)
            return t1 + j.tb;

        return -1;
    }
};

int main()
{
    int s, t, n, m;
    cin >> s >> t;
    --s, --t;
    cin >> n >> m;
    Graph g(n);
    vector<Node> nodes(n, Node());
    for (int i = 0; i < n; ++i)
    {
        char c;
        cin >> c >> nodes[i].rc >> nodes[i].tb >> nodes[i].tp;
        nodes[i].rc = nodes[i].tb - nodes[i].rc + (c == 'P' ? nodes[i].tp : 0);
    }
    while (m--)
    {
        int i, j, k;
        cin >> i >> j >> k;
        --i, --j;
        g.add(i, j, k);
        g.add(j, i, k);
    }
    cout << g.spfa(s, t, nodes) << endl;
    return 0;
}
