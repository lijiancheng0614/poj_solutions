#include <iostream>
#include <vector>
using namespace std;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef vector<vvb> vvvb;
int dx[] = {-1, 1, 0, 0, 0, 0};
int dy[] = {0, 0, -1, 1, 0, 0};
int dz[] = {0, 0, 0, 0, -1, 1};
class Solution
{
public:
    bool solve(vvvb & patterns0)
    {
        vector<vvvb> patterns(8, patterns0);
        n = patterns0[0].size();
        for (int i = 1; i < 4; ++i)
            for (int k = 0; k < 3; ++k)
                rotate(patterns[i][k], patterns[i - 1][k]);
        for (int i = 4; i < 8; ++i)
            for (int k = 0; k < 3; ++k)
                mirror(patterns[i][k], patterns[i - 4][k]);
        for (int i = 0; i < 8; ++i)
            for (int j = 0; j < 8; ++j)
                for (int k = 0; k < 8; ++k)
                {
                    get_cube(patterns[i][0], patterns[j][1], patterns[k][2]);
                    if (check_cube_patterns(patterns[i][0], patterns[j][1], patterns[k][2]) &&
                        check_cube_connectivity())
                        return true;
                }
        return false;
    }
private:
    vvvb cube, v;
    int n;
    void rotate(vvb & ans, vvb & pattern)
    {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                ans[i][j] = pattern[j][n - i - 1];
    }
    void mirror(vvb & ans, vvb & pattern)
    {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                ans[i][j] = pattern[i][n - j - 1];
    }
    void get_cube(vvb & pattern1, vvb & pattern2, vvb & pattern3)
    {
        cube.assign(n, vvb(n, vb(n, true)));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (!pattern1[i][j])
                    for (int k = 0; k < n; ++k)
                        cube[i][j][k] = false;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (!pattern2[i][j])
                    for (int k = 0; k < n; ++k)
                        cube[i][k][j] = false;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (!pattern3[i][j])
                    for (int k = 0; k < n; ++k)
                        cube[k][i][j] = false;
    }
    bool check_cube_patterns(vvb & pattern1, vvb & pattern2, vvb & pattern3)
    {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (pattern1[i][j])
                {
                    bool flag = true;
                    for (int k = 0; k < n; ++k)
                        if (cube[i][j][k])
                        {
                            flag = false;
                            break;
                        }
                    if (flag)
                        return false;
                }
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (pattern2[i][j])
                {
                    bool flag = true;
                    for (int k = 0; k < n; ++k)
                        if (cube[i][k][j])
                        {
                            flag = false;
                            break;
                        }
                    if (flag)
                        return false;
                }
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (pattern3[i][j])
                {
                    bool flag = true;
                    for (int k = 0; k < n; ++k)
                        if (cube[k][i][j])
                        {
                            flag = false;
                            break;
                        }
                    if (flag)
                        return false;
                }
        return true;
    }
    void dfs(int x, int y, int z)
    {
        v[x][y][z] = true;
        for (int k = 0; k < 6; ++k)
        {
            int xx = x + dx[k];
            int yy = y + dy[k];
            int zz = z + dz[k];
            if (xx >= 0 && xx < n && yy >= 0 && yy < n && zz >= 0 && zz < n &&
                cube[xx][yy][zz] && !v[xx][yy][zz])
                dfs(xx, yy, zz);
        }
    }
    bool check_cube_connectivity()
    {
        int x = -1, y = -1;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (cube[i][j][0])
                {
                    x = i;
                    y = j;
                    break;
                }
        if (x < 0)
            return false;
        v.assign(n, vvb(n, vb(n, false)));
        dfs(x, y, 0);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                for (int k = 0; k < n; ++k)
                    if (cube[i][j][k] && !v[i][j][k])
                        return false;
        return true;
    }
};

int main()
{
    int t = 0;
    int n;
    while (cin >> n && n)
    {
        vvvb patterns(3, vvb(n, vb(n, false)));
        for (int k = 0; k < 3; ++k)
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j)
                {
                    char c;
                    cin >> c;
                    patterns[k][i][j] = (c == 'X');
                }
        cout << "Data set " << ++t << ": ";
        cout << (Solution().solve(patterns) ? "Valid set of patterns" : "Impossible combination") << endl;
    }
    return 0;
}
