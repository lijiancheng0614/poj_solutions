#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef pair<int, int> pii;
const int oo = 10001;
class Solution
{
public:
    int solve(vector<pii> & a)
    {
        int n = a.size();
        sort(a.begin(), a.end(), greater<pii>());
        vector<int> f(n, oo);
        for (int i = 0; i < n; ++i)
            *lower_bound(f.begin(), f.end(), a[i].second) = a[i].second;
        return lower_bound(f.begin(), f.end(), oo) - f.begin();
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
        for (int i = 0; i < n; ++i)
        {
            int x, y;
            cin >> x >> y;
            a.push_back(pii(x, y));
        }
        cout << Solution().solve(a) << endl;
    }
    return 0;
}
