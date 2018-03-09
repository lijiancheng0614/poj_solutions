#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;
typedef vector<int> vi;
class Solution
{
public:
    vector<vi> solve(int n, const vi & a, const vi & b)
    {
        vector<vi> ans(n, vi(n, 0));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
            {
                int k = a[i * n + j];
                while (b[k] < 0)
                    k = (k - 1) / 4;
                ans[i][j] = b[k];
            }
        return ans;
    }
};

int main()
{
    int t;
    cin >> t;
    for (int tt = 1; tt <= t; ++tt)
    {
        int n, m;
        cin >> n >> m;
        vector<int> a(n * n, 0), b((n * n * 4 - 1) / 3, -1);
        while (m--)
        {
            int i, j;
            cin >> i >> j;
            a[j] = i;
        }
        cin >> m;
        while (m--)
        {
            int i, j;
            cin >> i >> j;
            b[i] = j;
        }
        cout << "Case " << tt << endl << endl;
        vector<vi> ans = Solution().solve(n, a, b);
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
                cout << setw(4) << ans[i][j];
            cout << endl;
        }
        cout << endl;
    }
    return 0;
}
