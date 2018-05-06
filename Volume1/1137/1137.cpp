#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;
class Graph
{
public:
    Graph(int n) : n(n)
    {
        a.assign(n, vi());
        b.assign(n, vi());
    }
    void add(int i, int j)
    {
        a[i].push_back(j);
    }
    void add2(int i, int j)
    {
        b[i].push_back(j);
    }
    void solve(vector<string> & outputs)
    {
        for (int i = 0; i < n; ++i)
        {
            sort(a[i].begin(), a[i].end());
            sort(b[i].begin(), b[i].end());
        }
        int x = 1 << 4, y = (1 << (n + 3)) + n - 1;
        int steps = bfs(x, y);
        if (steps < 0)
        {
            outputs.push_back("The problem cannot be solved.");
            return;
        }
        outputs.push_back("The problem can be solved in " + to_string(steps) + " steps:");
        for (; steps--; y = pre[y].first)
            if (pre[y].second >= n * 2)
                outputs.push_back("- Switch off light in room " + to_string(pre[y].second - n * 2 + 1) + ".");
            else if (pre[y].second >= n)
                outputs.push_back("- Switch on light in room " + to_string(pre[y].second - n + 1) + ".");
            else
                outputs.push_back("- Move to room " + to_string(pre[y].second + 1) + ".");
        reverse(outputs.begin() + 1, outputs.end());
    }
private:
    vvi a, b;
    int n;
    vector<pii> pre;
    inline string to_string(int n)
    {
        stringstream ss;
        ss << n;
        return ss.str();
    }
    int bfs(int x, int y)
    {
        queue<pii> q;
        int state_max = (1 << (n + 4)) + n;
        vector<bool> v(state_max, false);
        pre.assign(state_max, pii());
        v[x] = true;
        q.push(pii(x, 0));
        while (!q.empty())
        {
            pii h = q.front();
            q.pop();
            int state = h.first;
            int step = h.second;
            int k = state & 15;
            if (state == y)
                return step;
            for (int i = 0; i < a[k].size(); ++i)
            {
                int j = a[k][i];
                int state_new = state - k + j;
                if (!v[state_new] && ((state >> 4 >> j) & 1))
                {
                    v[state_new] = true;
                    q.push(pii(state_new, step + 1));
                    pre[state_new] = pii(state, j);
                }
            }
            for (int i = 0; i < b[k].size(); ++i)
            {
                int j = b[k][i];
                if (k == j)
                    continue;
                bool flag = (state >> 4 >> j) & 1;
                int state_new = state + (flag ? -1 : 1) * (16 << j);
                if (!v[state_new])
                {
                    v[state_new] = true;
                    q.push(pii(state_new, step + 1));
                    pre[state_new] = pii(state, j + n + flag * n);
                }
            }
        }
        return -1;
    }
};

int main()
{
    int t = 0;
    int r, d, s;
    while (cin >> r >> d >> s && r)
    {
        Graph g(r);
        while (d--)
        {
            int i, j;
            cin >> i >> j;
            --i, --j;
            g.add(i, j);
            g.add(j, i);
        }
        while (s--)
        {
            int i, j;
            cin >> i >> j;
            --i, --j;
            g.add2(i, j);
        }
        cout << "Villa #" << ++t << endl;
        vector<string> outputs;
        g.solve(outputs);
        for (int i = 0; i < outputs.size(); ++i)
            cout << outputs[i] << endl;
        cout << endl;
    }
    return 0;
}
