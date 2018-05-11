#include <iostream>
#include <vector>
#include <string>
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;
#define N 100
class Solution
{
public:
    string solve(const string & a)
    {
        dp(a);
        output = "";
        print(a, 0, int(a.length()) - 1);
        return output;
    }
private:
    vvi g;
    string output;
    void dp(const string & a)
    {
        int n = a.length();
        vvi f(n, vi(n, 0));
        g.assign(n, vi(n, -1));
        for (int i = 0; i < n; ++i)
            f[i][i] = 1;
        for (int l = 1; l < n; ++l)
            for (int i = 0; i + l < n; ++i)
            {
                int j = i + l;
                f[i][j] = f[i][i] + f[i + 1][j];
                g[i][j] = i;
                for (int k = i + 1; k < j; ++k)
                    if (f[i][k] + f[k + 1][j] < f[i][j])
                    {
                        f[i][j] = f[i][k] + f[k + 1][j];
                        g[i][j] = k;
                    }
                if (((a[i] == '(' && a[j] == ')') || (a[i] == '[' && a[j] == ']')) &&
                        f[i + 1][j - 1] < f[i][j])
                {
                    f[i][j] = f[i + 1][j - 1];
                    g[i][j] = -1;
                }
            }
    }
    void print(const string & a, int i, int j)
    {
        if (i > j)
            return;
        if (i == j)
        {
            output += a[i] == '(' || a[i] == ')' ? "()" : "[]";
            return;
        }
        if (~g[i][j])
        {
            print(a, i, g[i][j]);
            print(a, g[i][j] + 1, j);
        }
        else
        {
            output += a[i];
            print(a, i + 1, j - 1);
            output += a[i] == '(' ? ")" : "]";
        }
    }
};

int main()
{
    string a;
    cin >> a;
    cout << Solution().solve(a) << endl;
    return 0;
}
