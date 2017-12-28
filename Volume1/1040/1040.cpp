#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef pair<int, int> pii;
typedef pair<pii, int> piii;

class Solution
{
public:
    int solve(vector<piii> a, int n, int m)
    {
        sort(a.begin(), a.end());
        this->a = a;
        this->n = n;
        n_a = a.size();
        ans = 0;
        b.assign(n_a, pii(0, 0));
        for (int i = n_a - 1; i >= 0; --i)
        {
            b[i].second = b[i].first = (a[i].first.second - a[i].first.first) * a[i].second;
            if (i < n_a - 1)
                b[i].second += b[i + 1].second;
        }
        v.assign(m + 1, 0);
        dfs(0, 0);
        return ans;
    }
private:
    vector<piii> a;
    vector<pii> b;
    vector<int> v;
    int n, n_a, ans;
    void dfs(int k, int s)
    {
        if (k >= n_a)
        {
            ans = max(ans, s);
            return;
        }
        if (s + b[k].second <= ans)
            return;
        if (can(k))
        {
            for (int i = a[k].first.first; i < a[k].first.second; ++i)
                v[i] += a[k].second;
            dfs(k + 1, s + b[k].first);
            for (int i = a[k].first.first; i < a[k].first.second; ++i)
                v[i] -= a[k].second;
        }
        dfs(k + 1, s);
    }
    inline bool can(int k)
    {
        for (int i = a[k].first.first; i < a[k].first.second; ++i)
            if (v[i] + a[k].second > n)
                return false;
        return true;
    }
};

int main()
{
    int n, m, q;
    while (cin >> n >> m >> q && n + m + q)
    {
        vector<piii> a;
        while (q--)
        {
            int x, y, z;
            cin >> x >> y >> z;
            a.push_back(piii(pii(x, y), z));
        }
        cout << Solution().solve(a, n, m) << endl;
    }
    return 0;
}
