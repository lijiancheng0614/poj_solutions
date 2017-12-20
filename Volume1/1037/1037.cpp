#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
typedef vector<ll> vll;

class Solution
{
public:
    Solution(int n)
    {
        f.assign(n, vll(n, 0));
        g.assign(n, vll(n, 0));
        f[0][0] = g[0][0] = 1;
        for (int i = 1; i < n; ++i)
            for (int j = 0; j <= i; ++j)
            {
                for (int k = 0; k < j; ++k)
                    f[i][j] += g[i - 1][k];
                for (int k = j; k < i; ++k)
                    g[i][j] += f[i - 1][k];
            }
    }
    vector<int> solve(int n, ll c)
    {
        vector<int> ans;
        vector<bool> v(n, 0);
        for (int i = 0; i < n; ++i)
        {
            ll cc = 0;
            int k = 0;
            for (int j = 1; j <= n; ++j)
                if (!v[j])
                {
                    if (i == 0)
                        cc = f[n - 1][k] + g[n - 1][k];
                    else
                    {
                        if (j > ans[i - 1] && (i == 1 || ans[i - 2] > ans[i - 1]))
                            cc = f[n - 1 - i][k];
                        else if (j < ans[i - 1] && (i == 1 || ans[i - 2] < ans[i - 1]))
                            cc = g[n - 1 - i][k];
                    }
                    if (cc >= c)
                    {
                        v[j] = 1;
                        ans.push_back(j);
                        break;
                    }
                    else
                        c -= cc;
                    ++k;
                }
        }
        return ans;
    }
private:
    vector<vll> f, g;
};

int main()
{
    int t;
    cin >> t;
    Solution solution(20);
    while (t--)
    {
        int n;
        ll c;
        cin >> n >> c;
        vector<int> ans = solution.solve(n, c);
        for (int i = 0; i < n; ++i)
            cout << ans[i] << " ";
        cout << endl;
    }
    return 0;
}
