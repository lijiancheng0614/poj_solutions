#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    vector<int> solve(vector<int> & f, vector<int> & d, vector<int> & t, int h)
    {
        int n = f.size();
        vector<int> ans(n + 1, 0);
        ans[0] = h * 60;
        for (int i = 1; i < n - 1; ++i)
            t[i] += t[i - 1];
        for (int i = 0; i < n; ++i)
        {
            int time_left = h * 60 - (i > 0 ? t[i - 1] * 5 : 0);
            vector<int> ff;
            for (int j = 0; j <= i; ++j)
                ff.push_back(f[j]);
            vector<int> s(n + 1, 0);
            while (time_left >= 5)
            {
                int k = argmax(ff);
                s[k] += 5;
                s[n] += ff[k];
                ff[k] = max(ff[k] - d[k], 0);
                time_left -= 5;
            }
            if (s[n] > ans[n])
                ans = s;
        }
        return ans;
    }
private:
    int argmax(vector<int> & f)
    {
        int k = 0;
        for (int i = 1; i < f.size(); ++i)
            if (f[i] > f[k])
                k = i;
        return k;
    }
};

int main()
{
    int n;
    while (cin >> n && n)
    {
        int h;
        cin >> h;
        vector<int> f, d, t;
        for (int i = 0; i < n; ++i)
        {
            int x;
            cin >> x;
            f.push_back(x);
        }
        for (int i = 0; i < n; ++i)
        {
            int x;
            cin >> x;
            d.push_back(x);
        }
        for (int i = 0; i < n - 1; ++i)
        {
            int x;
            cin >> x;
            t.push_back(x);
        }
        vector<int> ans = Solution().solve(f, d, t, h);
        cout << ans[0];
        for (int i = 1; i < n; ++i)
            cout << ", " << ans[i];
        cout << endl;
        cout << "Number of fish expected: " << ans[n] << endl << endl;
    }
    return 0;
}
