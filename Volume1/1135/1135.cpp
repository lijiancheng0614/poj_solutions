#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
const int oo = 1 << 20;
typedef pair<int, int> pii;
typedef vector<pii> vpii;
typedef vector<vpii> vvpii;
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
    double solve(int & x, int & y)
    {
        spfa(0);
        int ans = 0;
        for (int k = 0; k < n; ++k)
        {
            if (d[k] * 2 >= ans)
            {
                ans = d[k] * 2;
                x = y = k;
            }
            for (int i = 0; i < a[k].size(); ++i)
            {
                int j = a[k][i].first;
                if (d[k] + d[j] + a[k][i].second > ans)
                {
                    ans = d[k] + d[j] + a[k][i].second;
                    x = k, y = j;
                }
            }
        }
        return ans / 2.0;
    }
private:
    vvpii a;
    int n;
    void spfa(int x)
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
                if (d[h] + a[h][i].second < d[j])
                {
                    d[j] = d[h] + a[h][i].second;
                    if (!v[j])
                    {
                        q.push(j);
                        v[j] = true;
                    }
                }
            }
            v[h] = false;
        }
    }
};

int main()
{
    int t = 0;
    int n, m;
    while (cin >> n >> m && n)
    {
        Graph g(n);
        while (m--)
        {
            int i, j, k;
            cin >> i >> j >> k;
            --i, --j;
            g.add(i, j, k);
            g.add(j, i, k);
        }
        cout << "System #" << ++t << endl;
        int x, y;
        double ans = g.solve(x, y);
        cout << "The last domino falls after " << fixed << setprecision(1) << ans << " seconds, ";
        if (x == y)
            cout << "at key domino " << x + 1;
        else
            cout << "between key dominoes " << x + 1 << " and " << y + 1;
        cout << "." << endl << endl;
    }
    return 0;
}
