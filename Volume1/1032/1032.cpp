#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    vector<int> solve(int n)
    {
        vector<int> ans;
        int s = 0;
        int k = 2;
        while (s + k <= n)
        {
            ans.push_back(k);
            s += k;
            ++k;
        }
        --k;
        s = n - s;
        if (s == k)
        {
            ans.erase(ans.begin());
            ans.push_back(k + 2);
        }
        else if (s > 0)
        {
            ans.erase(ans.begin() + k - s - 1);
            ans.push_back(k + 1);
        }
        return ans;
    }
};

int main()
{
    int n;
    cin >> n;
    vector<int> ans = Solution().solve(n);
    for (int i = 0; i < ans.size(); ++i)
        cout << ans[i] << " ";
    cout << endl;
    return 0;
}
