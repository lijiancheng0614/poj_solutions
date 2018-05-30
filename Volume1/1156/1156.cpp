#include <iostream>
using namespace std;
#define N 700
class Solution
{
public:
    int solve(const int a[][N], int n, int m, int c)
    {
        int ans = 0;
        for (int i = 0; i < m; ++i)
        {
            int f_min[n], f_max[n];
            for (int k = 0; k < n; ++k)
                f_min[k] = f_max[k] = a[k][i];
            for (int j = i + 1; j < m && j - i < 100; ++j)
            {
                for (int k = 0; k < n; ++k)
                {
                    f_min[k] = min(f_min[k], a[k][j]);
                    f_max[k] = max(f_max[k], a[k][j]);
                }
                int q1[n * 2], q2[n * 2];
                int f1 = 0, b1 = -1, f2 = 0, b2 = -1;
                int w = j - i + 1;
                for (int l = 0, r = 0; r < n && (n - l) * w > ans; ++r)
                {
                    while (f1 <= b1 && f_min[q1[b1]] > f_min[r])
                        --b1;
                    q1[++b1] = r;
                    while (f2 <= b2 && f_max[q2[b2]] < f_max[r])
                        --b2;
                    q2[++b2] = r;
                    while (l <= r && f1 <= b1 && f2 <= b2 &&
                            f_max[q2[f2]] - f_min[q1[f1]] > c)
                    {
                        ++l;
                        while (f1 <= b1 && q1[f1] < l)
                            ++f1;
                        while (f2 <= b2 && q2[f2] < l)
                            ++f2;
                    }
                    ans = max(ans, w * (r - l + 1));
                }
            }
        }
        return ans;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    int n, m, c;
    cin >> m >> n >> c;
    int a[n][N];
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> a[i][j];
    cout << Solution().solve(a, n, m, c) << endl;
    return 0;
}
