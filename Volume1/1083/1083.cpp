#include <iostream>
#include <vector>
using namespace std;
typedef pair<int, int> pii;
class Solution
{
public:
    int solve(const vector<pii> & a, const int m = 200)
    {
        vector<int> v(m, 0);
        for (int i = 0; i < a.size(); ++i)
        {
            int s = (min(a[i].first, a[i].second) - 1) / 2;
            int t = (max(a[i].first, a[i].second) - 1) / 2;
            for (int j = s; j <= t; ++j)
                v[j] += 10;
        }
        int ans = 0;
        for (int j = 0; j < m; ++j)
            ans = max(ans, v[j]);
        return ans;
    }
};

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        vector<pii> a;
        while (n--)
        {
            int x, y;
            cin >> x >> y;
            a.push_back(pii(x, y));
        }
        cout << Solution().solve(a) << endl;
    }
    return 0;
}
