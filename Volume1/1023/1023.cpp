#include <iostream>
#include <string>
using namespace std;
typedef long long ll;

class Solution
{
public:
    string solve(int k, string a, ll n)
    {
        string ans = "";
        for (int i = k - 1; i >= 0; --i)
        {
            ans = (n & 1 ? "1" : "0") + ans;
            n = (n - (n & 1) * (a[i] == 'p' ? 1 : -1)) >> 1;
        }
        if (n == 0)
            return ans;
        return "Impossible";
    }
};

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int k;
        string a;
        ll n;
        cin >> k;
        cin >> a;
        cin >> n;
        cout << Solution().solve(k, a, n) << endl;
    }
    return 0;
}
