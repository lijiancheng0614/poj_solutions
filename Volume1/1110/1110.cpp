#include <iostream>
#include <vector>
#include <string>
using namespace std;
typedef vector<string> vs;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;
class Solution
{
public:
    vs solve(vvvi & a)
    {
        n = a.size(), r = a[0].size(), c = a[0][0].size();
        for (int i = 0; i < n; ++i)
            if (!check(a, i))
                return vs(1, "impossible");
        vs outputs;
        for (int i = 0; i < r; ++i)
        {
            string line;
            for (int j = 0; j < n; ++j)
            {
                for (int k = 0; k < c; ++k)
                    if (a[j][i][k] == 2)
                        line += '#';
                    else if (a[j][i][k] == 1)
                        line += 'o';
                    else
                        line += '.';
                if (j < n - 1)
                    line += ' ';
            }
            outputs.push_back(line);
        }
        return outputs;
    }
private:
    int n, r, c;
    bool check(const vvvi & a, int i, int j, int k)
    {
        for (int ii = 0; ii < n; ++ii)
            if (ii != i && a[ii][j][k])
                return false;
        return true;
    }
    bool check(const vvvi & a, int i, int j, int k, int jj, int kk)
    {
        for (int ii = 0; ii < n; ++ii)
            if (ii != i && a[ii][j][k] && a[ii][jj][kk])
                return false;
        return true;
    }
    bool check(vvvi & a, int i)
    {
        for (int j = 0; j < r; ++j)
            for (int k = 0; k < c; ++k)
                if (a[i][j][k] && check(a, i, j, k))
                {
                    a[i][j][k] = 2;
                    return true;
                }
        for (int j = 0; j < r; ++j)
            for (int k = 0; k < c; ++k)
                if (a[i][j][k])
                    for (int jj = j; jj < r; ++jj)
                        for (int kk = jj == j ? k + 1 : 0; kk < c; ++kk)
                            if (a[i][jj][kk] && check(a, i, j, k, jj, kk))
                            {
                                a[i][j][k] = a[i][jj][kk] = 2;
                                return true;
                            }
        return false;
    }
};

int main()
{
    int t = 0;
    int n, r, c;
    while (cin >> n >> r >> c && n)
    {
        cout << "Test " << ++t << endl;
        vvvi a(n, vvi(r, vi(c, 0)));
        for (int i = 0; i < r; ++i)
            for (int j = 0; j < n; ++j)
            {
                string s;
                cin >> s;
                for (int k = 0; k < c; ++k)
                    a[j][i][k] = s[k] == 'o';
            }
        vs outputs = Solution().solve(a);
        for (int i = 0; i < outputs.size(); ++i)
            cout << outputs[i] << endl;
    }
    return 0;
}
