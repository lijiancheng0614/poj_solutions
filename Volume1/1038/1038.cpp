#include <iostream>
#include <vector>
using namespace std;
typedef vector<int> vi;
typedef vector<bool> vb;

class Solution
{
public:
    Solution(int m)
    {
        w.push_back(1);
        for (int j = 1; j <= m; ++j)
            w.push_back(w[j - 1] * 3);
    }
    int solve(vector<vb> a)
    {
        n = a.size();
        m = a[0].size();
        f.assign(2, vi(w[m], -1));
        int state = 0;
        for (int j = 0; j < m; ++j)
            state += w[j] * (a[0][j] + 1);
        f[1][state] = 0;
        for (int i = 1; i < n; ++i)
        {
            bool cur = i & 1;
            bool next = !cur;
            f[next].assign(w[m], - 1);
            for (int state = 0; state < w[m]; ++state)
            {
                if (f[cur][state] < 0)
                    continue;
                int state_next = 0;
                for (int j = 0; j < m; ++j)
                    if (a[i][j])
                        state_next += w[j] * 2;
                    else if (get_state(state, j) == 2)
                        state_next += w[j];
                dp(0, next, state, state_next, f[cur][state]);
            }
        }
        bool cur = n & 1;
        int ans = 0;
        for (int state = 0; state < w[m]; ++state)
            ans = max(ans, f[cur][state]);
        return ans;
    }
private:
    vector<vi> f;
    vi w;
    int n, m;
    void dp(int j, int next, int state, int state_next, int ff)
    {
        f[next][state_next] = max(f[next][state_next], ff);
        if (j < m - 1 && get_state(state, j) == 0 && get_state(state, j + 1) == 0 &&
            get_state(state_next, j) == 0 && get_state(state_next, j + 1) == 0)
            dp(j + 2, next, state, state_next + (w[j] + w[j + 1]) * 2, ff + 1);
        if (j < m - 2 && get_state(state_next, j) == 0 && get_state(state_next, j + 1) == 0 &&
            get_state(state_next, j + 2) == 0)
            dp(j + 3, next, state, state_next + (w[j] + w[j + 1] + w[j + 2]) * 2, ff + 1);
        if (j < m)
            dp(j + 1, next, state, state_next, ff);
    }
    inline int get_state(int state, int k)
    {
        return state / w[k] % 3;
    }
};

int main()
{
    int t;
    cin >> t;
    Solution solution(20);
    while (t--)
    {
        int n, m, k;
        cin >> n >> m >> k;
        vector<vb> a(n, vb(m, 0));
        while (k--)
        {
            int x, y;
            cin >> x >> y;
            --x, --y;
            a[x][y] = true;
        }
        cout << solution.solve(a) << endl;
    }
    return 0;
}
