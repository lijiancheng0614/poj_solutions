#include <iostream>
#include <vector>
using namespace std;
const int oo = 1 << 20;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
class Solution
{
public:
    pii solve(vvi & a)
    {
        int n = a.size();
        for (int k = 0; k < n; ++k)
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j)
                    a[i][j] = min(a[i][j], a[i][k] + a[k][j]);
        int len_min = oo;
        int k = -1;
        for (int i = 0; i < n; ++i)
        {
            int len_max = 0;
            for (int j = 0; j < n; ++j)
                if (j != i)
                    len_max = max(len_max, a[i][j]);
            if (len_max < len_min)
            {
                len_min = len_max;
                k = i;
            }
        }
        return pii(k + 1, len_min);
    }
};

int main()
{
    int n;
    while (cin >> n && n)
    {
        vvi a(n, vi(n, oo));
        for (int i = 0; i < n; ++i)
        {
            int k;
            cin >> k;
            while (k--)
            {
                int j;
                cin >> j;
                cin >> a[i][j - 1];
            }
        }
        pii ans = Solution().solve(a);
        if (ans.first)
            cout << ans.first << " " << ans.second << endl;
        else
            cout << "disjoint" << endl;
    }
    return 0;
}
