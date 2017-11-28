#include <iostream>
#include <cmath>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
    Solution()
    {
        group_len.push_back(0);
        tot_len.push_back(0);
        for (int i = 1; i < 31268; ++i)
        {
            group_len.push_back(group_len[i - 1] + (int)log10(i) + 1);
            tot_len.push_back(tot_len[i - 1] + group_len[i]);
        }
    }
    int solve(int n)
    {
        int group_id = lower_bound(tot_len.begin(), tot_len.end(), n) - tot_len.begin();
        n -= tot_len[group_id - 1];
        int num = lower_bound(group_len.begin(), group_len.end(), n) - group_len.begin();
        n -= group_len[num - 1];
        stringstream ss;
        ss << num;
        return ss.str()[n - 1] - '0';
    }
private:
    vector<int> group_len, tot_len;
};

int main()
{
    int t;
    cin >> t;
    Solution solution;
    while (t--)
    {
        int n;
        cin >> n;
        cout << solution.solve(n) << endl;
    }
    return 0;
}
