#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define N 10000000
#define N2 5000000
typedef long long ll;
class Solution
{
public:
    ll solve(vector<int> & a)
    {
        int n = a.size();
        sort(a.begin(), a.end());
        for (int i = 0; i < n; ++i)
            a.push_back(a[i] + N);
        ll s = 0;
        for (int i = 1; i < n; ++i)
            s += min((a[i] - a[0] + N) % N, (a[0] - a[i] + N) % N);
        int k = 0;
        while (a[k] - a[0] < N2)
            ++k;
        ll ans = s;
        for (int i = 1; i < n; ++i)
        {
            s -= (k - i) * (a[i] - a[i - 1]);
            s += (n - k + i) * (a[i] - a[i - 1]);
            while (a[k] - a[i] < N2)
            {
                s -= N + a[i] - a[k];
                s += a[k] - a[i];
                ++k;
            }
            ans = min(ans, s);
        }
        return ans;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    vector<int> a;
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        int x;
        cin >> x;
        a.push_back(x);
    }
    cout << Solution().solve(a) << endl;
    return 0;
}
