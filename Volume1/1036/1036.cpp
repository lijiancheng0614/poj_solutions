#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;

class Solution
{
public:
    int solve(vector<piii> a, int n, int k, int t)
    {
        a.push_back(piii(0, pii(0, 0)));
        ++n;
        sort(a.begin(), a.end());
        vector<int> f(n, 0);
        int ans = 0;
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < i; ++j)
                if (f[j] >= a[j].second.first && 
                    a[i].first - a[j].first >= abs(a[i].second.second - a[j].second.second))
                    f[i] = max(f[i], f[j] + a[i].second.first);
            ans = max(ans, f[i]);
        }
        return ans;
    }
};

int main()
{
    int n, k, t;
    cin >> n >> k >> t;
    vector<piii> a;
    for (int i = 0; i < n; ++i)
    {
        int x;
        cin >> x;
        a.push_back(piii(x, pii(0, 0)));
    }
    for (int i = 0; i < n; ++i)
        cin >> a[i].second.first;
    for (int i = 0; i < n; ++i)
        cin >> a[i].second.second;
    cout << Solution().solve(a, n, k, t) << endl;
    return 0;
}
