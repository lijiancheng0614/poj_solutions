#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    Solution(int maxk = 14)
    {
        ans.clear();
        for (int k = 1; k <= maxk; ++k)
        {
            int m = k + 1;
            while (true)
            {
                if (check(k, m))
                {
                    ans.push_back(m);
                    break;
                }
                else if (check(k, m + 1))
                {
                    ans.push_back(m + 1);
                    break;
                }
                m += k + 1;
            }
        }
    }
    int get_ans(int k)
    {
        return ans[k - 1];
    }
private:
    vector<int> ans;
    bool check(int k, int m)
    {
        int n = 2 * k;
        int x = 0;
        for (int i = 0; i < k; ++i)
        {
            x = (x + m - 1) % (n - i);
            if (x < k)
                return false;
        }
        return true;
    }
};

int main()
{
    int k;
    Solution solution;
    while (cin >> k && k)
        cout << solution.get_ans(k) << endl;
    return 0;
}
