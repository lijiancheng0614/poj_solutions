#include <iostream>
#include <vector>
#include <map>
using namespace std;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef pair<int, int> pii;
typedef pair<pii, int> piii;
const int dx[] = {0, 0, 1, -1};
const int dy[] = {-1, 1, 0, 0};
class Solution
{
public:
    int solve(const vvb & a, const vector<piii> & steps)
    {
        vector<vvb> f(2, a);
        int m = a.size(), n = a[0].size();
        bool kk = false;
        for (int k = steps.size() - 1; k >= 0; --k)
        {
            f[!kk].assign(m, vb(n, false));
            for (int i = 0; i < m; ++i)
                for (int j = 0; j < n; ++j)
                    if (f[kk][i][j])
                    {
                        int x = i, y = j;
                        int step_min = steps[k].first.first;
                        int d = steps[k].second;
                        while (step_min--)
                        {
                            x += dx[d];
                            y += dy[d];
                            if (x < 0 || x >= m || y < 0 || y >= n || !a[x][y])
                                break;
                        }
                        if (step_min >= 0)
                            continue;
                        int step = steps[k].first.second - steps[k].first.first + 1;
                        while (step--)
                        {
                            f[!kk][x][y] = true;
                            x += dx[d];
                            y += dy[d];
                            if (x < 0 || x >= m || y < 0 || y >= n || !a[x][y])
                                break;
                        }
                    }
            kk = !kk;
        }
        int s = 0;
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                if (f[kk][i][j])
                    ++s;
        return s;
    }
};

int main()
{
    map<char, int> map_direction;
    map_direction['R'] = 0;
    map_direction['L'] = 1;
    map_direction['U'] = 2;
    map_direction['D'] = 3;
    int t;
    cin >> t;
    while (t--)
    {
        int m, n;
        cin >> m >> n;
        vvb a(m, vb(n, true));
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
            {
                int x;
                cin >> x;
                if (x)
                    a[i][j] = false;
            }
        vector<piii> steps;
        int x, y;
        while (cin >> x >> y && x + y)
        {
            char c;
            cin >> c;
            steps.push_back(piii(pii(x, y), map_direction[c]));
        }
        cout << Solution().solve(a, steps) << endl;
    }
    return 0;
}
