#include <iostream>
#include <vector>
using namespace std;
class Solution
{
public:
    Solution(int n = 100) : n(n) {}
    int solve(int a, int b)
    {
        if (a > b)
            swap(a, b);
        v.assign(n, false);
        flag = false;
        if (!dfs(a, b) && flag)
            return a;
        return b;
    }
private:
    vector<bool> v;
    int n;
    bool flag;
    bool dfs(int a, int b)
    {
        if (a == 1)
        {
            if (b > 1)
            {
                flag = true;
                return dfs(b, 1);
            }
            return true;
        }
        for (int i = 2; i <= a && i <= n; ++i)
            if (a % i == 0 && !v[i])
            {
                v[i] = true;
                if (dfs(a / i, b))
                    return true;
                v[i] = false;
            }
        return false;
    }
};

int main()
{
    int a, b;
    Solution solution;
    while (cin >> a >> b)
        cout << solution.solve(a, b) << endl;
    return 0;
}
