#include <iostream>
#include <vector>
#include <map>
using namespace std;
class Solution
{
public:
    vector<int> solve(vector<int> & p)
    {
        vector<bool> a(p[0], false);
        a.push_back(true);
        for (int i = 1; i < p.size(); ++i)
        {
            for (int j = 0; j < p[i] - p[i - 1]; ++j)
                a.push_back(false);
            a.push_back(true);
        }
        int s = 0;
        map<int, int> left;
        vector<int> w;
        for (int i = 0; i < a.size(); ++i)
            if (a[i])
            {
                w.push_back((i - left[s] + 1) / 2);
                --s;
            }
            else
            {
                ++s;
                left[s] = i;
            }
        return w;
    }
};

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        vector<int> p;
        for (int i = 0; i < n; ++i)
        {
            int x;
            cin >> x;
            p.push_back(x);
        }
        vector<int> w = Solution().solve(p);
        for (int i = 0; i < w.size(); ++i)
            cout << w[i] << " ";
        cout << endl;
    }
    return 0;
}
