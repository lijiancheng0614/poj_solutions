#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef vector<pii> vpii;

class Solution
{
public:
    double solve(vector<vpii> a)
    {
        int n = a.size();
        vector<piii> d;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < a[i].size(); ++j)
                d.push_back(piii(a[i][j].first, pii(a[i][j].second, i)));
        sort(d.begin(), d.end());
        vector<bool> v(n, false);
        vector<int> min_p(n, 0);
        int sum_p = 0;
        double ans = 0;
        for (int i = d.size() - 1; i >= 0; --i)
        {
            int b = d[i].first;
            int p = d[i].second.first;
            int idx = d[i].second.second;
            if (!v[idx])
            {
                v[idx] = true;
                min_p[idx] = p;
                sum_p += p;
                --n;
            }
            else if (p < min_p[idx])
            {
                sum_p += p - min_p[idx];
                min_p[idx] = p;
            }
            if (!n)
                ans = max(ans, double(b) / sum_p);
        }
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
        vector<vpii> a;
        for (int i = 0; i < n; ++i)
        {
            int m;
            cin >> m;
            vpii aa;
            for (int j = 0; j < m; ++j)
            {
                int b, p;
                cin >> b >> p;
                aa.push_back(pii(b, p));
            }
            a.push_back(aa);
        }
        cout << setiosflags(ios::fixed) << setprecision(3) << Solution().solve(a) << endl;
    }
    return 0;
}