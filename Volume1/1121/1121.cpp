#include <iostream>
#include <string>
#include <vector>
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;
#define M 26
class Solution
{
public:
    void solve(vector<string> & outputs, vvi & a, const vvi & g)
    {
        int n = a.size();
        bool flag = true;
        while (flag)
        {
            flag = false;
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < g[i].size(); ++j)
                    for (int k = 0; k < M; ++k)
                        if (a[g[i][j]][k] == 1 && a[i][k] == 0)
                        {
                            a[i][k] = 1;
                            flag = true;
                        }
        }
        outputs.assign(n, ":");
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < 26; ++j)
                if (a[i][j] == 1)
                    outputs[i] += ('A' + j);
            outputs[i] += ":";
        }
    }
};

int main()
{
    int n;
    cin >> n;
    vvi a(n, vi(26, 0));
    for (int i = 0; i < n; ++i)
        for (int k = 1; k >= -1; k -= 2)
        {
            string s;
            cin >> s;
            if (s[0] == '.')
                continue;
            for (int j = 0; j < s.length(); ++j)
                a[i][s[j] - 'A'] = k;
        }
    vvi g(n, vi());
    int x, y;
    while (cin >> x >> y && x)
        g[y - 1].push_back(x - 1);
    vector<string> outputs;
    Solution().solve(outputs, a, g);
    for (int i = 0; i < outputs.size(); ++i)
        cout << outputs[i] << endl;
    return 0;
}
