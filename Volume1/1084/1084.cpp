#include <iostream>
#include <vector>
using namespace std;
typedef vector<bool> vb;
class DancingLinks
{
public:
    int solve(int n, int m, const vector<vb> & a)
    {
        h.assign(n + 1, -1);
        s.assign(m + 1, 0);
        h[0] = 0;
        l.clear();
        r.clear();
        u.clear();
        d.clear();
        c.clear();
        for (int i = 0; i <= m; ++i)
        {
            l.push_back(i - 1);
            r.push_back(i + 1);
            u.push_back(i);
            d.push_back(i);
            c.push_back(i);
        }
        l[0] = m;
        r[m] = 0;
        tot = m;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                if (a[i][j])
                    link(i, j);
        ans = n;
        dfs(0);
        return ans;
    }
private:
    vector<int> l, r, u, d, c, h, s;
    vb v;
    int m, tot, ans;
    void link(int i, int j)
    {
        ++tot;
        c.push_back(j);
        ++s[j];
        d.push_back(d[j]);
        u[d[j]] = tot;
        u.push_back(j);
        d[j] = tot;
        if (h[i] < 0)
        {
            h[i] = tot;
            l.push_back(tot);
            r.push_back(tot);
        }
        else
        {
            r.push_back(r[h[i]]);
            l[r[h[i]]] = tot;
            l.push_back(h[i]);
            r[h[i]] = tot;
        }
    }
    void remove(int k)
    {
        for (int i = d[k]; i != k; i = d[i])
        {
            l[r[i]] = l[i];
            r[l[i]] = r[i];
        }
    }
    void resume(int k)
    {
        for (int i = u[k]; i != k; i = u[i])
            l[r[i]] = r[l[i]] = i;
    }
    int get_h()
    {
        v.assign(m + 1, false);
        int ans = 0;
        for (int k = r[0]; k; k = r[k])
            v[k] = true;
        for (int k = r[0]; k; k = r[k])
            if (v[k])
            {
                v[k] = false;
                ++ans;
                for (int i = d[k]; i != k; i = d[i])
                    for (int j = r[i]; j != i; j = r[j])
                        v[c[j]] = false;
            }
        return ans;
    }
    void dfs(int x)
    {
        if (x + get_h() >= ans)
            return;
        if (!r[0])
        {
            ans = x;
            return;
        }
        int k = r[0];
        for (int i = r[0]; i; i = r[i])
            if (s[i] < s[k])
                k = i;
        for (int i = d[k]; i != k; i = d[i])
        {
            remove(i);
            for (int j = r[i]; j != i; j = r[j])
                remove(j);
            dfs(x + 1);
            for (int j = l[i]; j != i; j = l[j])
                resume(j);
            resume(i);
        }
    }
};
class Solution
{
public:
    Solution(int N = 61, int M = 56)
    {
        mark_missing.assign(N, false);
        a.assign(N, vb(M, false));
    }
    int solve(int n, const vector<int> & missing)
    {
        this->n = n;
        int r = n * (n + 1) * 2;
        for (int i = 0; i <= r; ++i)
            mark_missing[i] = false;
        for (int i = 0; i < missing.size(); ++i)
            mark_missing[missing[i]] = true;
        c = n * (n + 1) * (2 * n + 1) / 6;
        for (int i = 0; i <= r; ++i)
            for (int j = 0; j < c; ++j)
                a[i][j] = false;
        c = 0;
        for (int k = 0; k < n; ++k)
            for (int i = 1; i + k <= n; ++i)
                for (int j = 1; j + k <= n; ++j)
                    if (check(i, j, i + k, j + k))
                        add(i, j, i + k, j + k);
        return dlx.solve(r, c, a);
    }
private:
    int n, c;
    vb mark_missing;
    vector<vb> a;
    DancingLinks dlx;
    bool check(int x1, int y1, int x2, int y2)
    {
        for (int i = x1; i <= x2; ++i)
        {
            if (mark_missing[(i - 1) * (2 * n + 1) + n + y1])
                return false;
            if (mark_missing[(i - 1) * (2 * n + 1) + n + y2 + 1])
                return false;
        }
        for (int i = y1; i <= y2; ++i)
        {
            if (mark_missing[(x1 - 1) * (2 * n + 1) + i])
                return false;
            if (mark_missing[x2 * (2 * n + 1) + i])
                return false;
        }
        return true;
    }
    void add(int x1, int y1, int x2, int y2)
    {
        ++c;
        for (int i = x1; i <= x2; ++i)
        {
            a[(i - 1) * (2 * n + 1) + n + y1][c] = true;
            a[(i - 1) * (2 * n + 1) + n + y2 + 1][c] = true;
        }
        for (int i = y1; i <= y2; ++i)
        {
            a[(x1 - 1) * (2 * n + 1) + i][c] = true;
            a[x2 * (2 * n + 1) + i][c] = true;
        }
    }
};

int main()
{
    int t;
    cin >> t;
    Solution solution;
    while (t--)
    {
        int n, k;
        cin >> n >> k;
        vector<int> missing;
        while (k--)
        {
            int x;
            cin >> x;
            missing.push_back(x);
        }
        cout << solution.solve(n, missing) << endl;
    }
    return 0;
}
