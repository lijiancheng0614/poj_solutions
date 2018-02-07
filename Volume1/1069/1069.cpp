#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef vector<bool> vb;
class Solution
{
public:
    bool solve(int s, vector<int> & a)
    {
        this->s = s;
        r = s * 2;
        c = s * 4;
        int n = a.size();
        sort(a.begin(), a.end());
        for (int i = 0; i < n; ++i)
        {
            if (s % a[i] == 0)
                return true;
            if (a[i] > s)
                break;
            bool flag = true;
            for (int j = 0; j < b.size(); ++j)
                if (a[i] % b[j] == 0)
                {
                    flag = false;
                    break;
                }
            if (flag)
                b.push_back(a[i]);
        }
        init_board();
        return dfs(0, 0);
    }
private:
    vector<vb> a;
    vector<int> b;
    int s, r, c;
    void init_board()
    {
        a.assign(r, vb(c, true));
        for (int i = 0; i < s; ++i)
            for (int j = 0; j < (s + i) * 2 + 1; ++j)
                a[i][j] = false;
        for (int i = s; i < r; ++i)
            for (int j = (i - s) * 2 + 1; j < c; ++j)
                a[i][j] = false;
    }
    bool can_put(int x, int y, int k)
    {
        if (x + k > r || y + k > c)
            return false;
        if (y & 1)
        {
            for (int i = x; i < x + k; ++i)
                for (int j = y + (i - x) * 2; j < y + k * 2 - 1; ++j)
                    if (a[i][j])
                        return false;
        }
        else
        {
            for (int i = x; i < x + k; ++i)
                for (int j = y; j < y + (i - x) * 2 + 1; ++j)
                    if (a[i][j])
                        return false;
        }
        return true;
    }
    void put(int x, int y, int k, bool flag)
    {
        if (y & 1)
        {
            for (int i = x; i < x + k; ++i)
                for (int j = y + (i - x) * 2; j < y + k * 2 - 1; ++j)
                    a[i][j] = flag;
        }
        else
        {
            for (int i = x; i < x + k; ++i)
                for (int j = y; j < y + (i - x) * 2 + 1; ++j)
                    a[i][j] = flag;
        }
    }
    bool dfs(int x, int y)
    {
        if (x >= r)
            return true;
        if (y >= c)
            return dfs(x + 1, 0);
        if (a[x][y])
            for (int j = y + 1; y < c; ++j)
                if (!a[x][j])
                    return dfs(x, j);
        for (int i = 0; i < b.size(); ++i)
            if (can_put(x, y, b[i]))
            {
                put(x, y, b[i], true);
                if (dfs(x, y + 1))
                    return true;
                put(x, y, b[i], false);
            }
            else
                break;
        return false;
    }
};

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int s, n;
        cin >> s >> n;
        vector<int> a;
        for (int i = 0; i < n; ++i)
        {
            int x;
            cin >> x;
            a.push_back(x);
        }
        bool flag = Solution().solve(s, a);
        cout << (flag ? "YES" : "NO") << endl;
    }
    return 0;
}
