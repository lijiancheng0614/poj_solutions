#include <iostream>
#include <string>
#include <vector>
using namespace std;
typedef long long ll;
class Solution
{
public:
    Solution(int n = 19)
    {
        catalan.push_back(1);
        for (int i = 1; i < n; ++i)
            catalan.push_back((ll)catalan[i - 1] * (4 * i - 2) / (i + 1));
    }
    string solve(int n)
    {
        int i, s = 0;
        for (i = 1; s + catalan[i] < n; ++i)
            s += catalan[i];
        return dfs(i, n - s);
    }
private:
    vector<int> catalan;
    string dfs(int k, int n)
    {
        if (k == 1)
            return "X";
        int i, s = 0;
        for (i = 0; s + catalan[i] * catalan[k - i - 1] < n; ++i)
            s += catalan[i] * catalan[k - i - 1];
        n -= s + 1;
        string ans = "";
        if (i)
            ans += "(" + dfs(i, n / catalan[k - i - 1] + 1) + ")";
        ans += "X";
        if (k - i - 1)
            ans += "(" + dfs(k - i - 1, n % catalan[k - i - 1] + 1) + ")";
        return ans;
    }
};

int main()
{
    int n;
    Solution solution;
    while (cin >> n && n)
        cout << solution.solve(n) << endl;
    return 0;
}
