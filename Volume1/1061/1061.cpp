#include <iostream>
using namespace std;
typedef long long ll;
class Solution
{
public:
    ll solve(ll x, ll y, ll m, ll n, ll l)
    {
        ll a = n - m;
        ll b = l;
        ll c = x - y;
        ll t = exgcd(a, b, x, y);
        if (c % t)
            return -1;
        b /= t;
        x = c / t * x;
        return (x % b + b) % b;
    }
private:
    ll exgcd(ll a, ll b, ll & x, ll & y)
    {
        if (b == 0)
        {
            x = 1;
            y = 0;
            return a;
        }
        ll t = exgcd(b, a % b, y, x);
        y -= a / b * x;
        return t;
    }
};

int main()
{
    ll x, y, m, n, l;
    cin >> x >> y >> m >> n >> l;
    ll t = Solution().solve(x, y, m, n, l);
    if (t < 0)
        cout << "Impossible" << endl;
    else
        cout << t << endl;
    return 0;
}
