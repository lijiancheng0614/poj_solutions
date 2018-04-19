#include <iostream>
#include <string>
using namespace std;
class Solution
{
public:
    bool solve(const string & s)
    {
        int tot = 0;
        for (int i = s.length() - 1; i >= 0; --i)
            if (s[i] >= 'p' && s[i] <= 'z')
                ++tot;
            else if (s[i] == 'N')
            {
                if (tot < 1)
                    return false;
            }
            else if (s[i] == 'C' || s[i] == 'D' || s[i] == 'E' || s[i] == 'I')
            {
                if (tot < 2)
                    return false;
                --tot;
            }
            else
                return false;
        return tot == 1;
    }
};

int main()
{
    string s;
    while (cin >> s)
        cout << (Solution().solve(s) ? "YES" : "NO") << endl;
    return 0;
}
