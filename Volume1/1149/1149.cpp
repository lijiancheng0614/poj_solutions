#include <iostream>
#include <vector>
using namespace std;
const int oo = 1 << 30;
typedef vector<int> vi;
class Graph
{
public:
    int s, t;
    Graph(int n, int s, int t) : n(n), s(s), t(t)
    {
        b.assign(n, -1);
    }
    void add(int i, int j, int k)
    {
        a.push_back(Edge(b[i], j, k));
        b[i] = a.size() - 1;
        a.push_back(Edge(b[j], i, 0));
        b[j] = a.size() - 1;
    }
    int isap()
    {
        vi d(n, 0), h(n, 0), cur = b, pre(n, 0);
        pre[s] = s;
        h[0] = n;
        int x = oo, maxflow = 0;
        for (int k = s; d[s] < n; k = pre[k])
        {
            while (~cur[k])
            {
                int i = cur[k];
                int j = a[i].y;
                if (a[i].z && d[k] == d[j] + 1)
                {
                    pre[j] = k;
                    k = j;
                    x = min(x, a[i].z);
                    if (k == t)
                    {
                        maxflow += x;
                        while (k != s)
                        {
                            k = pre[k];
                            a[cur[k]].z -= x;
                            a[cur[k] ^ 1].z += x;
                        }
                        x = oo;
                    }
                    continue;
                }
                cur[k] = a[i].x;
            }
            int min_d = n;
            for (int i = b[k]; ~i; i = a[i].x)
            {
                int j = a[i].y;
                if (a[i].z && d[j] < min_d)
                {
                    min_d = d[j];
                    cur[k] = i;
                }
            }
            --h[d[k]];
            if (!h[d[k]])
                break;
            d[k] = min_d + 1;
            ++h[d[k]];
        }
        return maxflow;
    }
private:
    class Edge
    {
    public:
        int x, y, z;
        Edge(int x, int y, int z) : x(x), y(y), z(z) {}
    };
    vector<Edge> a;
    vi b;
    int n;
};

int main()
{
    int m, n;
    cin >> m >> n;
    Graph g(n + 2, n, n + 1);
    vi a(m, 0);
    for (int i = 0; i < m; ++i)
        cin >> a[i];
    vi v(m, -1);
    for (int i = 0; i < n; ++i)
    {
        int k;
        cin >> k;
        while (k--)
        {
            int j;
            cin >> j;
            --j;
            if (~v[j])
                g.add(v[j], i, oo);
            else
                g.add(g.s, i, a[j]);
                
            v[j] = i;
        }
        cin >> k;
        g.add(i, g.t, k);
    }
    cout << g.isap() << endl;
    return 0;
}
