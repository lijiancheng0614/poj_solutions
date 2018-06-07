#include <iostream>
#include <vector>
using namespace std;
const int oo = 1 << 20;
typedef vector<int> vi;
typedef vector<vi> vvi;
class Graph
{
public:
    vvi a;
    Graph(int n) : n(n)
    {
        a.assign(n, vi(n, oo));
        for (int i = 0; i < n; ++i)
            a[i][i] = 0;
    }
    void add(int i, int j)
    {
        a[i][j] = 1;
    }
    int solve(const vi & p, const vvi & region)
    {
        floyd();
        int ans = oo;
        for (int i = 0; i < n; ++i)
        {
            int s = 0;
            for (int j = 0; j < p.size(); ++j)
            {
                int mi = oo;
                for (int k = 0; k < region[p[j]].size(); ++k)
                    mi = min(mi, a[i][region[p[j]][k]]);
                s += mi;
                if (s >= ans)
                    break;
            }
            ans = min(ans, s);
        }
        return ans;
    }
private:
    int n;
    void floyd()
    {
        for (int k = 0; k < n; ++k)
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j)
                    a[i][j] = min(a[i][j], a[i][k] + a[k][j]);
    }
};

int main()
{
    int m, n, l;
    cin >> m >> n >> l;
    vi p(l, 0);
    for (int i = 0; i < l; ++i)
    {
        cin >> p[i];
        --p[i];
    }
    vvi region(n, vi());
    vvi v(n, vi(n, -1));
    Graph g(m);
    for (int i = 0; i < m; ++i)
    {
        int k, x, y;
        cin >> k;
        cin >> x;
        --x;
        region[x].push_back(i);
        int head = x;
        while (k--)
        {
            if (k)
            {
                cin >> y;
                --y;
                region[y].push_back(i);
            }
            else
                y = head;
            if (~v[x][y])
            {
                g.add(i, v[x][y]);
                g.add(v[x][y], i);
            }
            else
                v[x][y] = v[y][x] = i;
            x = y;
        }
    }
    cout << g.solve(p, region) << endl;
    return 0;
}
