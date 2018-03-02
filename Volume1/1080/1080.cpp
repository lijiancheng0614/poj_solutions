#include <iostream>
#include <string>
#include <vector>
using namespace std;
typedef vector<int> vi;
const string letters = "ACGT";
const int score[][5] = {
    5, -1, -2, -1, -3,
    -1, 5, -3, -2, -4,
    -2, -3, 5, -2, -2,
    -1, -2, -2, 5, -1,
    -3, -4, -2, -1, -5
};
class Solution
{
public:
    int solve(const string & a, const string & b)
    {
        int n = a.length();
        int m = b.length();
        vector<vi> f(n + 1, vi(m + 1, 0));
        int index_space = index(' ');
        for (int i = 1; i <= n; ++i)
            f[i][0] = f[i - 1][0] + score[index(a[i - 1])][index_space];
        for (int j = 1; j <= m; ++j)
            f[0][j] = f[0][j - 1] + score[index_space][index(b[j - 1])];
        for (int i = 1; i <= n; ++i)
        {
            int x = index(a[i - 1]);
            for (int j = 1; j <= m; ++j)
            {
                int y = index(b[j - 1]);
                f[i][j] = max(f[i - 1][j - 1] + score[x][y],
                              max(f[i - 1][j] + score[x][index_space],
                                  f[i][j - 1] + score[index_space][y]));
            }
        }
        return f[n][m];
    }
private:
    inline int index(char c)
    {
        for (int i = 0; i < 4; ++i)
            if (c == letters[i])
                return i;
        return 4;
    }
};

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, m;
        string a, b;
        cin >> n >> a;
        cin >> m >> b;
        cout << Solution().solve(a, b) << endl;
    }
    return 0;
}
