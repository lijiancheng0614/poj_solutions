#include <iostream>
#include <vector>
using namespace std;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;

class Solution
{
public:
    int solve(vector<piii> d)
    {
        int n = d.size();
        for (int i = 0; i < n; ++i)
            d[i].second.second -= d[i].second.first;
        int k = 0;
        int ans = d[0].first + d[0].second.second * k;
        while (ans < 10000)
        {
            bool flag = true;
            for (int i = 1; i < n; ++i)
                if (ans < d[i].first || (ans - d[i].first) % d[i].second.second)
                {
                    flag = false;
                    break;
                }
            if (flag)
                return ans;
            ++k;
            ans = d[0].first + d[0].second.second * k;
        }
        return -1;
    }
};

int main()
{
    int n, t = 0;
    while (cin >> n && n)
    {
        vector<piii> d;
        for (int i = 0; i < n; ++i)
        {
            int y, a, b;
            cin >> y >> a >> b;
            d.push_back(piii(y, pii(a, b)));
        }
        int ans = Solution().solve(d);
        cout << "Case #" << ++t << ":" << endl;
        if (ans < 0)
            cout << "Unknown bugs detected." << endl << endl;
        else
            cout << "The actual year is " << ans << "." << endl << endl;
    }
    return 0;
}
