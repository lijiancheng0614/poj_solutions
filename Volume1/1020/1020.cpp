#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
    string solve(int s, int n, vector<int> a)
    {
        d.assign(11, 0);
        int area = 0;
        int count_half = 0;
        for (int i = 0; i < n; ++i)
        {
            ++d[a[i]];
            area += a[i] * a[i];
            if (a[i] > s / 2)
                ++count_half;
        }
        if (count_half > 1 || area != s * s)
            return "HUTUTU!";
        this->s = s;
        col.assign(s, s);
        return dfs(n) ? "KHOOOOB!" : "HUTUTU!";
    }
private:
    vector<int> d, col;
    int s;
    bool dfs(int nn)
    {
        if (nn <= 0)
            return true;
        int c = 0;
        for (int i = 1; i < s; ++i)
            if (col[i] > col[c])
                c = i;
        for (int k = 10; k; --k)
            if (d[k] > 0 && col[c] >= k && s - c >= k)
            {
                int width = 1;
                for (int i = c + 1; i < c + k; ++i)
                    if (col[i] == col[c])
                        ++width;
                    else
                        break;
                if (width == k)
                {
                    --d[k];
                    for (int i = c; i < c + k; ++i)
                        col[i] -= k;
                    if (dfs(nn - 1))
                        return true;
                    for (int i = c; i < c + k; ++i)
                        col[i] += k;
                    ++d[k];
                }
            }
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
        cout << Solution().solve(s, n, a) << endl;
    }
    return 0;
}