#include <iostream>
#include <vector>
#include <stack>
using namespace std;
typedef pair<int, int> pii;

class Solution
{
public:
    vector<pii> solve(vector<int> a)
    {
        vector<pii> ans;
        stack<int> s;
        int n = a.size() - 1;
        for (int i = 1; i <= n; ++i)
            if (a[i] == i)
                continue;
            else if (a[i] == 0)
                continue;
            else
            {
                s.push(i);
                bool is_circle = false;
                int j = a[i], k;
                while (a[j])
                {
                    if (a[j] == i)
                    {
                        is_circle = true;
                        break;
                    }
                    s.push(j);
                    j = a[j];
                }
                if (is_circle)
                {
                    for (k = n; k; --k)
                        if (a[k] == 0)
                            break;
                    ans.push_back(pii(j, k));
                    a[k] = a[j];
                }
                while (!s.empty())
                {
                    int top = s.top();
                    ans.push_back(pii(top, j));
                    a[j] = a[top];
                    j = top;
                    s.pop();
                }
                if (is_circle)
                {
                    a[j] = a[k];
                    ans.push_back(pii(k, j));
                    j = k;
                }
                a[j] = 0;
            }
        return ans;
    }
};

int main()
{
    int n, k, m = 0;
    cin >> n >> k;
    vector<int> a(n + 1, 0);
    while (k--)
    {
        int s;
        cin >> s;
        while (s--)
        {
            int x;
            cin >> x;
            a[x] = ++m;
        }
    }
    vector<pii> ans = Solution().solve(a);
    if (ans.size() == 0)
        cout << "No optimization needed" << endl;
    else
    {
        for (int i = 0; i < ans.size(); ++i)
            cout << ans[i].first << " " << ans[i].second << endl;
    }
    return 0;
}
