#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;
const int oo = 1 << 30;
typedef pair<string, string> pss;
typedef vector<string> vs;
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
class Solution
{
public:
    int solve(const vs & a, const vs & b, const vector<pss> & c)
    {
        int n = a.size();
        int m = b.size();
        int k = c.size();
        int tot = n + m * 2 + k * 2;
        h_n = m;
        Graph g(tot + 2, tot, tot + 1);
        for (int i = 0; i < n; ++i)
            g.add(get_id(a[i]), g.t, 1);
        for (int i = 0; i < m; ++i)
        {
            g.add(g.s, i, 1);
            g.add(i, get_id(b[i]), 1);
        }
        for (int i = 0; i < k; ++i)
        {
            int x = get_id(c[i].first);
            int y = get_id(c[i].second);
            g.add(x, y, oo);
        }
        return m - g.isap();
    }
private:
    map<string, int> h;
    int h_n;
    inline int get_id(const string & x)
    {
        if (!h[x])
            h[x] = h_n++;
        return h[x];
    }
};

int main()
{
    int n;
    cin >> n;
    vs a;
    while (n--)
    {
        string x;
        cin >> x;
        a.push_back(x);
    }
    cin >> n;
    vs b;
    while (n--)
    {
        string x, y;
        cin >> x >> y;
        b.push_back(y);
    }
    cin >> n;
    vector<pss> c;
    while (n--)
    {
        string x, y;
        cin >> x >> y;
        c.push_back(pss(x, y));
    }
    cout << Solution().solve(a, b, c) << endl;
    return 0;
}
