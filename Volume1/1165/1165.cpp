#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;
#define N 100000
#define n 5
#define n2 24
const int pos_x[] =
{
    0, 1, 2, 3, 4, 4, 4, 4, 4, 1, 2, 3, 1, 3, 0, 2, 3, 3, 2, 0, 2, 1, 0, 1
};
const int pos_y[] =
{
    4, 4, 4, 4, 4, 0, 1, 2, 3, 1, 2, 3, 3, 1, 3, 3, 0, 2, 1, 1, 0, 2, 2, 0
};
const int tag[] =
{
    0, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 3, 0, 4, 0, 1, 0, 2, 0, 1, 2, 0, 1, 2
};
class Solution
{
public:
    vvi solve(int s, int x)
    {
        this->s = s;
        a.assign(n, vi(n, -1));
        a[0][0] = x;
        init_primes();
        dfs(0);
        sort(ans.begin(), ans.end());
        return ans;
    }
private:
    vvi a, ans;
    vi p;
    vector<bool> v;
    int s;
    void init_primes()
    {
        v.assign(N, false);
        v[1] = true;
        for (int i = 2; i < N; ++i)
        {
            if (!v[i])
                p.push_back(i);
            for (int j = 0; j < p.size() && i * p[j] < N; ++j)
            {
                v[i * p[j]] = true;
                if (i % p[j] == 0)
                    break;
            }
        }
    }
    inline bool check_row(int x)
    {
        int num = 0, sum = 0;
        for (int j = 0; j < n; ++j)
            if (~a[x][j])
            {
                num = num * 10 + a[x][j];
                sum += a[x][j];
            }
            else
                return true;
        return !v[num] && sum == s;
    }
    inline bool check_col(int y)
    {
        int num = 0, sum = 0;
        for (int i = 0; i < n; ++i)
            if (~a[i][y])
            {
                num = num * 10 + a[i][y];
                sum += a[i][y];
            }
            else
                return true;
        return !v[num] && sum == s;
    }
    inline bool check_diag1()
    {
        int num = 0, sum = 0;
        for (int i = 0; i < n; ++i)
            if (~a[i][i])
            {
                num = num * 10 + a[i][i];
                sum += a[i][i];
            }
            else
                return true;
        return !v[num] && sum == s;
    }
    inline bool check_diag2()
    {
        int num = 0, sum = 0;
        for (int i = n - 1; i >= 0; --i)
            if (~a[i][n - 1 - i])
            {
                num = num * 10 + a[i][n - 1 - i];
                sum += a[i][n - 1 - i];
            }
            else
                return true;
        return !v[num] && sum == s;
    }
    inline bool check(int x, int y)
    {
        if ((x == 0 || y == 0) && !a[x][y])
            return false;
        if (!check_row(x))
            return false;
        if (!check_col(y))
            return false;
        if (x == y && !check_diag1())
            return false;
        if (x + y == n - 1 && !check_diag2())
            return false;
        return true;
    }
    void dfs(int k)
    {
        if (k == n2)
        {
            vi mat;
            for (int i = 0; i < n; ++i)
            {
                int num = 0;
                for (int j = 0; j < n; ++j)
                    num = num * 10 + a[i][j];
                mat.push_back(num);
            }
            ans.push_back(mat);
            return;
        }
        int x = pos_x[k], y = pos_y[k];
        if (tag[k] == 1)
        {
            int sum = 0;
            for (int i = 0; i < n; ++i)
                if (~a[i][y])
                    sum += a[i][y];
            a[x][y] = s - sum;
            if (a[x][y] >= 0 && a[x][y] <= 9 && check(x, y))
                dfs(k + 1);
            a[x][y] = -1;
        }
        else if (tag[k] == 2)
        {
            int sum = 0;
            for (int j = 0; j < n; ++j)
                if (~a[x][j])
                    sum += a[x][j];
            a[x][y] = s - sum;
            if (a[x][y] >= 0 && a[x][y] <= 9 && check(x, y))
                dfs(k + 1);
            a[x][y] = -1;
        }
        else if (tag[k] == 3)
        {
            int sum = 0;
            for (int i = 0; i < n; ++i)
                if (~a[i][i])
                    sum += a[i][i];
            a[x][y] = s - sum;
            if (a[x][y] >= 0 && a[x][y] <= 9 && check(x, y))
                dfs(k + 1);
            a[x][y] = -1;
        }
        else if (tag[k] == 4)
        {
            int sum = 0;
            for (int i = 0; i < n; ++i)
                if (~a[i][n - 1 - i])
                    sum += a[i][n - 1 - i];
            a[x][y] = s - sum;
            if (a[x][y] >= 0 && a[x][y] <= 9 && check(x, y))
                dfs(k + 1);
            a[x][y] = -1;
        }
        else
        {
            for (int i = x == 0 || y == 0 || x == n - 1 || y == n - 1;
                    i <= 9; i += (x == n - 1 || y == n - 1) + 1)
            {
                a[x][y] = i;
                if (check(x, y))
                    dfs(k + 1);
                a[x][y] = -1;
            }
        }
    }
};

int main()
{
    int s, x;
    cin >> s >> x;
    vvi ans = Solution().solve(s, x);
    for (int i = 0; i < ans.size(); ++i)
    {
        for (int j = 0; j < ans[i].size(); ++j)
            cout << ans[i][j] << endl;
        cout << endl;
    }
    return 0;
}
