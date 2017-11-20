#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
    int solve(vector<int> a, int s)
    {
        sort(a.begin(), a.end(), greater<int>());
        this->a = a;
        n = a.size();
        for (int x = a[0]; x * 2 <= s; ++x)
        {
            if (s % x)
                continue;
            v.assign(n, 0);
            if (dfs(0, 0, 0, x))
                return x;
        }
        return s;
    }
private:
    vector<int> a;
    vector<bool> v;
    int n;
    bool dfs(int k, int pre, int s, int x)
    {
        if (k >= n)
            return 1;
        for (int i = pre; i < n; ++i)
        {
            if (v[i])
                continue;
            if (i && a[i] == a[i - 1] && !v[i - 1])
                continue;
            v[i] = 1;
            if (s + a[i] < x)
            {
                if (dfs(k + 1, i + 1, s + a[i], x))
                    return 1;
            }
            else if (s + a[i] == x)
            {
                if (dfs(k + 1, 0, 0, x))
                    return 1;
            }
            v[i] = 0;
            if (s == 0)
                break;
        }
        return 0;
    }
};

int main()
{
    int n;
    while (cin >> n && n)
    {
        vector<int> a;
        int s = 0;
        for (int i = 0; i < n; ++i)
        {
            int x;
            cin >> x;
            a.push_back(x);
            s += x;
        }
        cout << Solution().solve(a, s) << endl;
    }
    return 0;
}
