#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;
const int oo = 1 << 30;
class Graph
{
public:
    vi d, pre;
    void spfa(int y, const vvi & a)
    {
        int n = a.size();
        queue<int> q;
        vector<bool> v(n, false);
        d.assign(n, oo);
        pre.assign(n, -1);
        q.push(y);
        v[y] = true;
        d[y] = 0;
        while (!q.empty())
        {
            int h = q.front();
            q.pop();
            for (int i = 0; i < n; ++i)
                if (i != h && a[i][h] >= 0 && d[h] + a[i][h] < d[i])
                {
                    d[i] = d[h] + a[i][h];
                    pre[i] = h;
                    if (!v[i])
                    {
                        q.push(i);
                        v[i] = true;
                    }
                }
            v[h] = false;
        }
    }
};

int main()
{
    int n;
    cin >> n;
    vvi a(n, vi(n, 0));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> a[i][j];
    int x, y;
    cin >> y;
    --y;
    Graph g;
    g.spfa(y, a);
    vector<pii> ans;
    while (cin >> x)
    {
        --x;
        ans.push_back(pii(g.d[x], x));
    }
    sort(ans.begin(), ans.end());
    cout << "Org\tDest\tTime\tPath" << endl;
    for (int i = 0; i < ans.size(); ++i)
    {
        cout << ans[i].second + 1 << "\t" << y + 1 << "\t" << ans[i].first;
        for (int k = ans[i].second; k >= 0; k = g.pre[k])
            cout << "\t" << k + 1;
        cout << endl;
    }
    return 0;
}
