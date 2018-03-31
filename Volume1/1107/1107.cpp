#include <iostream>
#include <vector>
#include <string>
using namespace std;
typedef vector<int> vi;
class Solution
{
public:
    string solve(const vi & k, const string & s)
    {
        vector<vi> a(3, vi());
        for (int i = 0; i < s.length(); ++i)
            if (s[i] >= 'a' && s[i] <= 'i')
                a[0].push_back(i);
            else if (s[i] >= 'j' && s[i] <= 'r')
                a[1].push_back(i);
            else
                a[2].push_back(i);
        string ans = s;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < a[i].size(); ++j)
            {
                int pos = (j + k[i]) % a[i].size();
                ans[a[i][pos]] = s[a[i][j]];
            }
        return ans;
    }
};

int main()
{
    vi k(3, 0);
    string s;
    while (cin >> k[0] >> k[1] >> k[2] && k[0])
    {
        cin >> s;
        cout << Solution().solve(k, s) << endl;
    }
    return 0;
}
