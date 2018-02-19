#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
using namespace std;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef vector<pii> vpii;
class Solution
{
public:
    int solve(int x, int y, vector<vpii> & links, const vector<piii> & pipes)
    {
        int n = pipes.size();
        if (y < pipes[x].second.first)
            return -1;
        if (y <= pipes[x].second.second)
            links[x].push_back(pii(y, -2));
        set<int> y_link;
        for (int i = 0; i < links.size(); ++i)
            for (int j = 0; j < links[i].size(); ++j)
                y_link.insert(links[i][j].first);
        for (int i = 0; i < n; ++i)
        {
            for (set<int>::const_iterator j = y_link.lower_bound(pipes[i].second.first);
                j != y_link.end() && *j < pipes[i].second.second; ++j)
                links[i].push_back(pii(*j, i));
            links[i].push_back(pii(pipes[i].second.first, -1));
            sort(links[i].begin(), links[i].end());
        }
        priority_queue<pii> q;
        vector<int> water(n, -1);
        water[0] = pipes[0].second.second;
        q.push(pii(water[0], 0));
        int total = 0;
        while (!q.empty())
        {
            pii h = q.top();
            int w = h.first;
            int k = h.second;
            q.pop();
            if (k == -2)
                return total;
            if (k == -1)
                return -1;
            total += water[k] - w;
            water[k] = w;
            for (int i = links[k].size() - 1; i >= 0 && links[k][i].first == w; --i)
            {
                int j = links[k][i].second;
                if (j < 0)
                    q.push(pii(links[k][i]));
                else if (water[j] < 0)
                {
                    water[j] = pipes[j].second.second;
                    q.push(pii(water[j], j));
                }
                links[k].pop_back();
            }
            if (!links[k].empty())
                q.push(pii(links[k].back().first, k));
        }
        return -1;
    }
};

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        vector<piii> pipes;
        cin >> n;
        for (int i = 0; i < n; ++i)
        {
            int x, y, height;
            cin >> x >> y >> height;
            pipes.push_back(piii(x, pii(y, y + height)));
        }
        int m;
        vector<vpii> links(n, vpii());
        cin >> m;
        for (int i = 0; i < m; ++i)
        {
            int x, y, length;
            cin >> x >> y >> length;
            int p1 = -1, p2 = -1;
            for (int j = 0; j < n && (p1 < 0 || p2 < 0); ++j)
                if (pipes[j].first + 1 == x)
                    p1 = j;
                else if (pipes[j].first == x + length)
                    p2 = j;
            links[p1].push_back(pii(y, p2));
            links[p2].push_back(pii(y, p1));
        }
        int x, y;
        cin >> x >> y;
        int ans = Solution().solve(x - 1, y, links, pipes);
        if (ans < 0)
            cout << "No Solution" << endl;
        else
            cout << ans << endl;
    }
    return 0;
}
