#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef vector<int> vi;
int cnt[3][3] =
{
    {5, 6, 8},
    {5, 7, 7},
    {5, 7, 7}
};
class Solution
{
public:
    int solve(vector<vi> & a)
    {
        for (int i = 0; i < a.size(); ++i)
            sort(a[i].begin(), a[i].end());
        int s_max = 0;
        for (int k = 0; k < 3; ++k)
        {
            int s = 0;
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    s += a[i][j] * cnt[(i + k) % 3][j];
            s_max = max(s_max, s);
        }
        return s_max;
    }
};

int main()
{
    int t;
    cin >> t;
    for (int tt = 1; tt <= t; ++tt)
    {
        vector<vi> a(3, vi(3, 0));
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                cin >> a[i][j];
        cout << "Test #" << tt << endl;
        cout << Solution().solve(a) << endl << endl;
    }
    return 0;
}
