#include <iostream>
#include <queue>
#include <vector>
using namespace std;
typedef pair<int, int> pii;
typedef pair<pii, int> piii;
typedef vector<bool> vb;
typedef vector<vb> vvb;
const int dx[] = {-1, 1, 0, 0, 0, 0};
const int dy[] = {0, 0, -1, 1, 0, 0};
const int dz[] = {0, 0, 0, 0, -1, 1};
class Solution
{
public:
    int solve(int n, int m, int k, const vector<piii> & a)
    {
        n += 2, m += 2, k += 2;
        vector<vvb> g(n, vvb(m, vb(k, false)));
        for (int i = 0; i < a.size(); ++i)
            g[a[i].first.first][a[i].first.second][a[i].second] = true;
        queue<piii> q;
        q.push(piii(pii(0, 0), 0));
        vector<vvb> v(n, vvb(m, vb(k, false)));
        v[0][0][0] = true;
        int ans = 0;
        while (!q.empty())
        {
            piii h = q.front();
            q.pop();
            int x = h.first.first;
            int y = h.first.second;
            int z = h.second;
            for (int i = 0; i < 6; ++i)
            {
                int xx = x + dx[i];
                int yy = y + dy[i];
                int zz = z + dz[i];
                if (xx >= 0 && xx < n && yy >= 0 && yy < m && zz >= 0 && zz < k)
                {
                    if (!g[xx][yy][zz])
                    {
                        if (!v[xx][yy][zz])
                        {
                            q.push(piii(pii(xx, yy), zz));
                            v[xx][yy][zz] = true;
                        }
                    }
                    else
                        ++ans;
                }
            }
        }
        return ans;
    }
};

int main()
{
    int n, m, k, l;
    while (cin >> n >> m >> k >> l && n)
    {
        vector<piii> a;
        while (l--)
        {
            int x;
            cin >> x;
            a.push_back(piii(pii(x % (n * m) % n + 1, x % (n * m) / n + 1), x / (n * m) + 1));
        }
        cout << "The number of faces needing shielding is " << Solution().solve(n, m, k, a) << "." << endl;
    }
    return 0;
}
