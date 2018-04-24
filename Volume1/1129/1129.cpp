#include <iostream>
#include <string>
#include <vector>
using namespace std;
typedef vector<bool> vb;
class Solution
{
public:
    int solve(const vector<vb> & a)
    {
        int ans = 0;
        n = a.size();
        v.assign(n, false);
        for (int i = 0; i < n; ++i)
            if (!v[i])
            {
                v[i] = true;
                color(i, a);
                ++ans;
            }
        return ans;
    }
private:
    vb v;
    int n;
    void color(int k, const vector<vb> & a)
    {
        vector<int> c;
        c.push_back(k);
        for (int i = k + 1; i < n; ++i)
            if (!v[i] && !a[k][i])
            {
                bool flag = true;
                for (int j = 0; j < c.size(); ++j)
                    if (a[i][c[j]])
                    {
                        flag = false;
                        break;
                    }
                if (flag)
                {
                    v[i] = true;
                    c.push_back(i);
                }
            }
    }
};

int main()
{
    int n;
    while (cin >> n && n)
    {
        vector<vb> a(n, vb(n, false));
        for (int i = 0; i < n; ++i)
        {
            string line;
            cin >> line;
            for (int j = 2; j < line.length(); ++j)
                a[i][line[j] - 'A'] = true;
        }
        int ans = Solution().solve(a);
        cout << ans;
        if (ans == 1)
            cout << " channel needed." << endl;
        else
            cout << " channels needed." << endl;
    }
    return 0;
}
