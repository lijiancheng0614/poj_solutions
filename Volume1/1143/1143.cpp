#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef vector<int> vi;
#define N 20
class Solution
{
public:
    Solution()
    {
        f.assign((1 << (N - 1)) + 1, 0);
    }
    vi solve(vi & a)
    {
        sort(a.begin(), a.end());
        vi ans;
        int state = 0;
        for (int i = 0; i < a.size(); ++i)
            state |= 1 << (a[i] - 2);
        for (int i = 0; i < a.size(); ++i)
            if (!dp(state, a[i]))
                ans.push_back(a[i]);
        return ans;
    }
private:
    vi f;
    inline bool get_state(int state, int i)
    {
        return (state >> (i - 2)) & 1;
    }
    bool dp(int state, int k)
    {
        state -= 1 << (k - 2);
        for (int i = 2; i + k <= N; ++i)
            if (!get_state(state, i) && get_state(state, i + k))
                state -= 1 << (i + k - 2);
        if (f[state])
            return f[state] > 0;
        for (int i = 2; i <= N; ++i)
            if (get_state(state, i) && !dp(state, i))
            {
                f[state] = 1;
                return true;
            }
        f[state] = -1;
        return false;
    }
};

int main()
{
    int t = 0;
    int n;
    Solution solution;
    while (cin >> n && n)
    {
        vi a;
        while (n--)
        {
            int x;
            cin >> x;
            a.push_back(x);
        }
        cout << "Test Case #" << ++t << endl;
        vi ans = solution.solve(a);
        if (ans.size())
        {
            cout << "The winning moves are:";
            for (int i = 0; i < ans.size(); ++i)
                cout << " " << ans[i];
            cout << endl;
        }
        else
            cout << "There's no winning move." << endl;
        cout << endl;
    }
    return 0;
}
