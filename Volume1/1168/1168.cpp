#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;
class Solution
{
public:
    int solve(int n, int m, int k, vvi & ans)
    {
        this->n = n;
        this->m = m;
        ans_max = -1;
        a.assign(n, -1);
        for (int i = 0; i < n; ++i)
            p.push_back(i);
        v.assign(m + n * (n - 1) + 2, false);
        do
        {
            dfs(0, k, ans);
        } while (next_permutation(p.begin() + 1, p.end()));
        sort(ans.begin(), ans.end());
        ans.resize(unique(ans.begin(), ans.end()) - ans.begin());
        return ans_max;
    }
private:
    vi a, p;
    vector<bool> v;
    int n, m;
    int ans_max;
    inline int get_next()
    {
        int x = m;
        while (v[x])
            ++x;
        return x;
    }
    void dfs(int k, int x, vvi & ans)
    {
        int next = get_next();
        if (k == n)
        {
            int ma = next - 1;
            if (ma > ans_max)
                ans.assign(1, a);
            else if (ma == ans_max)
                ans.push_back(a);
            ans_max = max(ans_max, ma);
            return;
        }
        for (; x <= next; ++x)
        {
            vector<bool> vv = v;
            a[p[k]] = x;
            for (int i = 0; i < n; ++i)
                if (~a[i])
                {
                    int s = a[i];
                    v[s] = true;
                    for (int j = (i + 1) % n; ~a[j] && j != i; j = (j + 1) % n)
                    {
                        s += a[j];
                        v[s] = true;
                    }
                }
            dfs(k + 1, x, ans);
            v = vv;
        }
        a[p[k]] = -1;
    }
};

int main()
{
    int n, m, k;
    cin >> n >> m >> k;
    vvi ans;
    cout << Solution().solve(n, m, k, ans) << endl;
    for (int i = 0; i < ans.size(); ++i)
    {
        for (int j = 0; j < ans[i].size(); ++j)
            cout << ans[i][j] << " ";
        cout << endl;
    }
    return 0;
}
