#include <iostream>
#include <vector>
#include <string>
using namespace std;
typedef vector<int> vi;
class Solution
{
public:
    vector<string> solve(const vector<vi> & a)
    {
        int n = a.size();
        int h = 4 * n - 1, w = 4 * n + 3;
        b.assign(h, string(w, ' '));
        for (int i = 0; i < h; ++i)
            b[i][0] = b[i][w - 1] = '*';
        for (int j = 0; j < w; ++j)
            b[0][j] = b[h - 1][j] = '*';
        for (int i = 1; i <= h - 2; i += 4)
        {
            for (int j = 1; j <= w - 2; j += 4)
                b[i][j] = 'H';
            for (int j = 3; j <= w - 2; j += 4)
                b[i][j] = 'O';
        }
        for (int i = 3; i <= h - 3; i += 4)
            for (int j = 3; j <= w - 4; j += 4)
                b[i][j] = 'H';
        for (int i = 0; i < n; ++i)
        {
            int x = i * 4 + 1;
            for (int j = 0; j < n; ++j)
            {
                int y = j * 4 + 3;
                if (a[i][j] == 1)
                {
                    b[x][y - 1] = '-';
                    b[x][y + 1] = '-';
                }
                else  if (a[i][j] == -1)
                {
                    b[x + 1][y] = '|';
                    b[x - 1][y] = '|';
                }
            }
        }
        for (int i = 0; i < n; ++i)
        {
            int x = i * 4 + 1;
            for (int j = 0; j < n; ++j)
                if (a[i][j] == 0)
                {
                    int y = j * 4 + 3;
                    if (check(x, y - 2))
                        b[x][y - 1] = '-';
                    else
                        b[x][y + 1] = '-';
                    if (x - 2 > 0 && check(x - 2, y))
                        b[x - 1][y] = '|';
                    else
                        b[x + 1][y] = '|';
                }
        }
        return b;
    }
private:
    vector<string> b;
    bool check(int i, int j)
    {
        return b[i - 1][j] != '|' && b[i + 1][j] != '|' && b[i][j - 1] != '-' && b[i][j + 1] != '-';
    }
};

int main()
{
    int t = 0, n;
    while (cin >> n && n)
    {
        vector<vi> a(n, vi(n, 0));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                cin >> a[i][j];
        cout << "Case " << ++t << ":" << endl << endl;
        vector<string> outputs = Solution().solve(a);
        for (int i = 0; i < outputs.size(); ++i)
            cout << outputs[i] << endl;
        cout << endl;
    }
    return 0;
}
