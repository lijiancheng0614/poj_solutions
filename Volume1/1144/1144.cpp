#include <iostream>
#include <sstream>
#include <vector>
using namespace std;
typedef vector<int> vi;
class Graph
{
public:
    Graph(int n) : n(n)
    {
        a.assign(n, vi());
    }
    void add(int i, int j)
    {
        a[i].push_back(j);
    }
    int count_cut()
    {
        s = 0;
        n_subtrees = 0;
        v.assign(n, false);
        cut.assign(n, false);
        dfn.assign(n, 0);
        low.assign(n, 0);
        tarjan(0);
        int ans = n_subtrees >= 2;
        for (int i = 1; i < n; ++i)
            ans += cut[i];
        return ans;
    }
private:
    vector<vi> a;
    vi dfn, low;
    vector<bool> v, cut;
    int n, s, n_subtrees;
    void tarjan(int k)
    {
        dfn[k] = low[k] = ++s;
        v[k] = true;
        for (int i = 0; i < a[k].size(); ++i)
        {
            int j = a[k][i];
            if (!dfn[j])
            {
                tarjan(j);
                low[k] = min(low[k], low[j]);
                if (k == 0)
                    ++n_subtrees;
                else if (dfn[k] <= low[j])
                    cut[k] = 1;
            }
            else if (v[j])
                low[k] = min(low[k], dfn[j]);
        }
    }
};

int main()
{
    int n;
    while (cin >> n && n)
    {
        Graph g(n);
        int i;
        while (cin >> i && i)
        {
            --i;
            int j;
            string line;
            getline(cin, line);
            stringstream ss(line);
            while (ss >> j)
            {
                --j;
                g.add(i, j);
                g.add(j, i);
            }
        }
        cout << g.count_cut() << endl;
    }
    return 0;
}
