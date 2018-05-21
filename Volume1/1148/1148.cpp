#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef vector<int> vi;
class Solution
{
public:
    bool solve(vi & ans_x, vi & ans_y, vi & a, const vi & signs_x, const vi & signs_y)
    {
        int n = signs_x.size();
        sort(a.begin(), a.end());
        for (int i = n - 1, k = signs_x[n - 1]; i >= 0; --i, k *= -1)
            a[i] *= k;
        for (int i = 2 * n - 1, k = signs_y[n - 1]; i >= n; --i, k *= -1)
            a[i] *= k;
        int mid_x = 0, mid_y = 0;
        for (int i = 1; i < n; ++i)
        {
            if (signs_x[i] == signs_x[i - 1])
                ++mid_x;
            if (signs_y[i] == signs_y[i - 1])
                ++mid_y;
        }
        if (!check(ans_x, signs_x, a, 0, mid_x) ||
                !check(ans_y, signs_y, a, n, mid_y))
            return false;
        return true;
    }
private:
    bool check(vi & ans, const vi & signs, const vi & a, int offset, int mid)
    {
        if (a[mid + offset] * signs[0] < 0)
            return false;
        ans.push_back(a[mid + offset]);
        int l = mid, r = mid;
        for (int i = 1; i < signs.size(); ++i)
            if (a[r + offset] * signs[i] > 0)
            {
                --l;
                if (l < 0)
                    return false;
                ans.push_back(a[l + offset]);
            }
            else
            {
                ++r;
                if (r >= signs.size())
                    return false;
                ans.push_back(a[r + offset]);
            }
        return true;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    vi a(n * 2, 0);
    for (int i = 0; i < n * 2; ++i)
        cin >> a[i];
    vi signs_x(n, 0), signs_y(n, 0);
    for (int i = 0; i < n; ++i)
    {
        int x;
        cin >> x;
        signs_x[i] = (x == 1 || x == 4) * 2 - 1;
        signs_y[i] = (x <= 2) * 2 - 1;
    }
    vi ans_x, ans_y;
    if (Solution().solve(ans_x, ans_y, a, signs_x, signs_y))
    {
        for (int i = 0; i < n; ++i)
        {
            if (ans_x[i] > 0)
                cout << "+";
            cout << ans_x[i] << " ";
            if (ans_y[i] > 0)
                cout << "+";
            cout << ans_y[i] << endl;
        }
    }
    else
        cout << 0 << endl;
    return 0;
}
