#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;
class Solution
{
public:
    int dp(vvi & a)
    {
        int n = a.size();
        for (int i = n - 2; i >= 0; --i)
            for (int j = 0; j <= i; ++j)
                a[i][j] += max(a[i + 1][j], a[i + 1][j + 1]);
        return a[0][0];
    }
};

int main()
{
    int n;
    cin >> n;
    vvi a;
    for (int i = 0; i < n; ++i)
    {
        vi aa;
        for (int j = 0; j <= i; ++j)
        {
            int x;
            cin >> x;
            aa.push_back(x);
        }
        a.push_back(aa);
    }
    cout << Solution().dp(a) << endl;
    return 0;
}
