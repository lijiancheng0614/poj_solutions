#include <iostream>
#include <cctype>
#include <string>
#include <vector>
using namespace std;
#define N 16
typedef vector<string> vs;
int ship_rotation[7] = {1, 2, 2, 4, 4, 4, 2};
string ships[7][4][4] =
{
    "xx  ", "xx  ", "    ", "    ",
    "    ", "    ", "    ", "    ",
    "    ", "    ", "    ", "    ",
    "    ", "    ", "    ", "    ",
    "xx  ", " xx ", "    ", "    ",
    " x  ", "xx  ", "x   ", "    ",
    "    ", "    ", "    ", "    ",
    "    ", "    ", "    ", "    ",
    " xx ", "xx  ", "    ", "    ",
    "x   ", "xx  ", " x  ", "    ",
    "    ", "    ", "    ", "    ",
    "    ", "    ", "    ", "    ",
    "x   ", "xxx ", "    ", "    ",
    "xx  ", "x   ", "x   ", "    ",
    "xxx ", "  x ", "    ", "    ",
    " x  ", " x  ", "xx  ", "    ",
    "  x ", "xxx ", "    ", "    ",
    "xx  ", " x  ", " x  ", "    ",
    "xxx ", "x   ", "    ", "    ",
    "x   ", "x   ", "xx  ", "    ",
    " x  ", "xxx ", "    ", "    ",
    " x  ", "xx  ", " x  ", "    ",
    "xxx ", " x  ", "    ", "    ",
    "x   ", "xx  ", "x   ", "    ",
    "xxxx", "    ", "    ", "    ",
    "x   ", "x   ", "x   ", "x   ",
    "    ", "    ", "    ", "    ",
    "    ", "    ", "    ", "    ",
};
class Solution
{
public:
    bool solve(vs & a)
    {
        h = a.size();
        w = a[0].size();
        n_dot = 0;
        for (int i = 0; i < h; ++i)
            for (int j = 0; j < w; ++j)
                n_dot += a[i][j] == '.';
        n_ans = 0;
        dfs(0, a);
        if (n_ans == 1)
            return true;
        if (n_ans > n_dot || !n_ans)
            return false;
        bool flag = true;
        while (flag)
        {
            flag = false;
            for (int x = 0; x < h; ++x)
                for (int y = 0; y < w; ++y)
                {
                    if (a[x][y] != '.')
                        continue;
                    int s = 0, k;
                    for (int i = 0; i < n_ans; ++i)
                        if (!ans[i][x][y])
                        {
                            ++s;
                            k = i;
                        }
                    if (s == 1)
                    {
                        for (int i = 0; i < h; ++i)
                            for (int j = 0; j < w; ++j)
                                ans[k][i][j] = ans[n_ans - 1][i][j];
                        --n_ans;
                        flag = true;
                    }
                }
        }
        return n_ans < 2;
    }
private:
    bool ans[100][N][N];
    int h, w, n_dot, n_ans;
    bool check(int k, int x, int y, int d, const vs & a)
    {
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                if (ships[k][d][i][j] != 'x')
                    continue;
                else if (x + i < 0 || x + i >= h || y + j < 0 || y + j >= w)
                    return false;
                else if (a[x + i][y + j] != '.' && a[x + i][y + j] != 'x')
                    return false;
        return true;
    }
    bool equals(bool a[N][N], bool b[N][N])
    {
        for (int x = 0; x < h; ++x)
            for (int y = 0; y < w; ++y)
                if (a[x][y] != b[x][y])
                    return false;
        return true;
    }
    void dfs(int k, vs & a)
    {
        if (n_ans > n_dot)
            return;
        if (k >= 7)
        {
            for (int x = 0; x < h; ++x)
                for (int y = 0; y < w; ++y)
                    if (a[x][y] == 'x')
                        return;
                    else
                        ans[n_ans][x][y] = isdigit(a[x][y]);
            for (int i = 0; i < n_ans; ++i)
                if (equals(ans[i], ans[n_ans]))
                    return;
            ++n_ans;
            return;
        }
        vs aa = a;
        for (int x = 0; x < h; ++x)
            for (int y = 0; y < w; ++y)
                for (int d = 0; d < ship_rotation[k]; ++d)
                    if (check(k, x, y, d, a))
                    {
                        for (int i = 0; i < 4; ++i)
                            for (int j = 0; j < 4; ++j)
                                if (ships[k][d][i][j] == 'x')
                                    a[x + i][y + j] = k + '0';
                        dfs(k + 1, a);
                        a = aa;
                    }
    }
};

int main()
{
    int t = 0;
    int h, w;
    while (cin >> h >> w && h)
    {
        vs a(h, "");
        for (int i = 0; i < h; ++i)
            cin >> a[i];
        cout << "Game #" << ++t << endl;
        cout << (Solution().solve(a) ? "yes" : "no") << "." << endl << endl;
    }
    return 0;
}
