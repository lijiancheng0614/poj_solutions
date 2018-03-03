#include <iostream>
#include <vector>
using namespace std;
typedef vector<int> vi;
class Solution
{
public:
    int solve(const vector<vi> & a)
    {
        int n = a.size();
        vi f(n, (1 << n) - 1);
        for (int i = 0; i < a.size(); ++i)
        {
            f[i] -=  1 << i;
            for (int j = 0; j < a[i].size(); ++j)
                f[i] -= 1 << a[i][j];
        }
        int m = n / 2;
        int ans = m + 1;
        int state_last = (1 << n) - (1 << (n - m));
        for (int state = (1 << m) - 1; state <= state_last; state = next_state(state))
        {
            int count[2] = {0, 0};
            for (int i = 0; i < n; ++i)
                if ((state >> i) & 1)
                    count[0] = max(count[0], __builtin_popcount(f[i] & state));
                else
                    count[1] = max(count[1], __builtin_popcount(f[i] & (~state)));
            ans = min(ans, max(count[0], count[1]));
        }
        return ans;
    }
private:
    int next_state(int state)
    {
        int low_bit = state & -(signed)state;
        int next = state + low_bit;
        int ones = state ^ next;
        ones = (ones / low_bit) >> 2;
        return next | ones;
    }
};

int main()
{
    vector<vi> a(30, vi());
    int i, n = 0;
    while (cin >> i)
    {
        --i;
        int k;
        cin >> k;
        while (k--)
        {
            int j;
            cin >> j;
            a[i].push_back(j - 1);
        }
        n = max(n, i);
    }
    a.erase(a.begin() + n + 1, a.end());
    cout << Solution().solve(a) << endl;
    return 0;
}
