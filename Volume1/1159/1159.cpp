#include <iostream>
#include <string>
#include <vector>
using namespace std;
typedef vector<int> vi;
class Solution
{
public:
    int dp(const string & a)
    {
        int n = a.length();
        vector<vi> f(2, vi(n + 1, 0));
        for (int i = 0; i <= n; ++i)
            for (int j = 0; j <= n; ++j)
                if (i == 0 || j == 0)
                    continue;
                else if (a[i - 1] == a[n - j])
                    f[i & 1][j] = f[(i - 1) & 1][j - 1] + 1;
                else
                    f[i & 1][j] = max(f[i & 1][j - 1], f[(i - 1) & 1][j]);
        return n - f[n & 1][n];
    }
};

int main()
{
    int n;
    string a;
    cin >> n;
    cin >> a;
    cout << Solution().dp(a) << endl;
    return 0;
}
