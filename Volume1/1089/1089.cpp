#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef pair<int, int> pii;
class Solution
{
public:
    vector<pii> solve(vector<pii> & a)
    {
        vector<pii> ans;
        sort(a.begin(), a.end());
        int x = a[0].first, y = a[0].second;
        for (int i = 0; i < a.size(); ++i)
            if (y < a[i].first)
            {
                ans.push_back(pii(x, y));
                x = a[i].first;
                y = a[i].second;
            }
            else if (y < a[i].second)
                y = a[i].second;
        ans.push_back(pii(x, y));
        return ans;
    }
};

int main()
{
    int n;
    cin >> n;
    vector<pii> a;
    for (int i = 0; i < n; ++i)
    {
        int x, y;
        cin >> x >> y;
        a.push_back(pii(x, y));
    }
    vector<pii> ans = Solution().solve(a);
    for (int i = 0; i < ans.size(); ++i)
        cout << ans[i].first << " " << ans[i].second << endl;
    return 0;
}
