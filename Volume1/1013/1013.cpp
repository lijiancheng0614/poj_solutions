#include <iostream>
#include <cstdlib>
#include <string>
#include <map>
using namespace std;

class Solution
{
public:
    Solution()
    {
        h.clear();
        v.clear();
    }
    void update(string a, string b, string status)
    {
        int n = a.length();
        if (status[0] == 'u')
        {
            for (int i = 0; i < n; ++i)
            {
                ++h[a[i]];
                --h[b[i]];
            }
        }
        else if (status[0] == 'd')
        {
            for (int i = 0; i < n; ++i)
            {
                --h[a[i]];
                ++h[b[i]];
            }
        }
        else
        {
            for (int i = 0; i < n; ++i)
                v[a[i]] = v[b[i]] = true;
        }
    }
    void get_ans()
    {
        char ans = 'L';
        for (char i = 'A'; i < 'L'; ++i)
        {
            if (v[i])
                continue;
            if (abs(h[i]) >= abs(h[ans]))
                ans = i;
        }
        cout << ans << " is the counterfeit coin and it is ";
        if (h[ans] > 0)
            cout << "heavy." << endl;
        else
            cout << "light." << endl;
    }
private:
    map<char, int> h;
    map<char, bool> v;
};

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        Solution solution;
        for (int i = 0; i < 3; ++i)
        {
            string a, b, status;
            cin >> a >> b >> status;
            solution.update(a, b, status);
        }
        solution.get_ans();
    }
    return 0;
}
