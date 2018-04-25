#include <iostream>
#include <queue>
#include <vector>
using namespace std;
typedef vector<int> vi;
class Solution
{
public:
    int solve(const vector<vi> & g, int t)
    {
        this->t = t;
        n = g.size();
        v.assign(n, false);
        count.assign(n, 0);
        path.assign(n, 0);
        dfs(0, 0, g);
        bfs(0, t, g);
        count[0] = count[t];
        int ans = pre[t];
        for (int i = pre[t]; ~i; i = pre[i])
            if (count[i] > count[ans])
                ans = i;
        return ans;
    }
private:
    vector<bool> v;
    vi count;
    vi path;
    vi pre;
    int n, t;
    void dfs(int k, int depth, const vector<vi> & g)
    {
        if (k == t)
        {
            for (int i = 0; i < depth; ++i)
                ++count[path[i]];
            return ;
        }
        for (int i = 0; i < g[k].size(); ++i)
        {
            int j = g[k][i];
            if (v[j])
                continue;
            v[j] = true;
            path[depth] = j;
            dfs(j, depth + 1, g);
            v[j] = false;
        }
    }
    void bfs(int x, int y, const vector<vi> & g)
    {
        queue<int> q;
        q.push(x);
        v.assign(n, false);
        v[x] = true;
        pre.assign(n, -1);
        while (!q.empty())
        {
            int h = q.front();
            q.pop();
            if (h == y)
                break;
            for (int i = 0; i < g[h].size(); ++i)
            {
                int j = g[h][i];
                if (v[j])
                    continue;
                v[j] = true;
                pre[j] = h;
                q.push(j);
            }
        }
    }
};

int main()
{
    int n, t;
    cin >> n >> t;
    vector<vi> g(n, vi());
    int x, y;
    while (cin >> x >> y)
        g[x].push_back(y);
    cout << "Put guards in room " << Solution().solve(g, t) << "." << endl;
    return 0;
}
