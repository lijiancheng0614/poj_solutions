#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef pair<int, int> pii;
class Shelf
{
public:
    int x, y, l, x1, x2;
    Shelf() {}
    Shelf(int x, int y, int l, int x1, int x2) : x(x), y(y), l(l), x1(x1), x2(x2) {}
    bool operator<(const Shelf & s) const
    {
        return y < s.y;
    }
};
class Solution
{
public:
    pii solve(vector<Shelf> & a, int xn, int yn, int xt, int yt)
    {
        pii ans(1 << 30, 1 << 30);
        sort(a.begin(), a.end());
        for (int i = 0; i < a.size(); ++i)
        {
            if (a[i].y + yt > yn)
                break;
            if (a[i].l < xt)
                continue;
            for (int x = 0; x + xt <= xn; ++x)
            {
                if (x + a[i].l < a[i].x1)
                    continue;
                if (a[i].x2 + a[i].l < x + xt)
                    break;
                ans = min(ans, get_operations_count(i, x, a, xn, xt, yt));
            }
        }
        return ans;
    }
private:
    pii get_operations_count(int k, int x, const vector<Shelf> & a, int xn, int xt, int yt)
    {
        int pegs = 2 * (a[k].x1 - x) > a[k].l || 2 * (x + xt - a[k].x2) > a[k].l ||
                   a[k].x2 - x > a[k].l || x + xt - a[k].x1 > a[k].l;
        int planks = 0;
        for (int i = k + 1; i < a.size(); ++i)
        {
            if (a[i].y >= a[k].y + yt)
                break;
            if (a[i].x + a[i].l <= x || a[i].x >= x + xt)
                continue;
            if (a[i].x2 <= x)
            {
                int rest = x - a[i].x1 <= a[i].x1 ? 2 * (x - a[i].x1) : x;
                if (rest < a[i].l)
                    planks += a[i].l - rest;
            }
            else if (a[i].x1 >= x + xt)
            {
                int rest = a[i].x2 - x - xt <= xn - a[i].x2 ? 2 * (a[i].x2 - x - xt) : xn - x - xt;
                if (rest < a[i].l)
                    planks += a[i].l - rest;
            }
            else if (a[i].x1 <= x && a[i].x2 > x && a[i].x2 < x + xt)
            {
                if (x == 0)
                {
                    pegs += 2;
                    planks += a[i].l;
                }
                else
                {
                    ++pegs;
                    if (a[i].l > x)
                        planks += a[i].l - x;
                }
            }
            else if (a[i].x1 > x && a[i].x1 < x + xt && a[i].x2 >= x + xt)
            {
                if (x + xt == xn)
                {
                    pegs += 2;
                    planks += a[i].l;
                }
                else
                {
                    ++pegs;
                    if (a[i].l > xn - x - xt)
                        planks += a[i].l - xn + x + xt;
                }
            }
            else if (a[i].x1 <= x && a[i].x2 >= x + xt)
            {
                if (x == 0 && xt == xn)
                    pegs += 2;
                else
                    ++pegs;
                int rest = max(x, xn - x - xt);
                if (a[i].l > rest)
                    planks += a[i].l - rest;
            }
            else if (a[i].x1 > x && a[i].x2 < x + xt)
            {
                pegs += 2;
                planks += a[i].l;
            }
        }
        return pii(pegs, planks);
    }
};

int main()
{
    int n, xn, yn, xt, yt;
    cin >> xn >> yn >> xt >> yt;
    cin >> n;
    vector<Shelf> a;
    while (n--)
    {
        int x, y, l, x1, x2;
        cin >> y >> x >> l >> x1 >> x2;
        x1 += x;
        x2 += x;
        a.push_back(Shelf(x, y, l, x1, x2));
    }
    pii ans = Solution().solve(a, xn, yn, xt, yt);
    cout << ans.first << " " << ans.second << endl;
    return 0;
}
