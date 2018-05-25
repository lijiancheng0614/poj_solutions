#include <iostream>
#include <sstream>
#include <string>
using namespace std;
class Solution
{
public:
    string solve(const string & s)
    {
        int n = 0;
        int m = 0;
        for (int i = 0; i < s.length(); ++i)
        {
            int x = to_int(s[i]);
            m += x;
            n = max(n, x);
        }
        for (++n; n < 63; ++n)
            if (m % (n - 1) == 0)
                return to_string(n);
        return "such number is impossible!";
    }
private:
    inline int to_int(char c)
    {
        if (c >= '0' && c <= '9')
            return c - '0';
        if (c >= 'A' && c <= 'Z')
            return c - 'A' + 10;
        return c - 'a' + 36;
    }
    inline string to_string(int n)
    {
        stringstream ss;
        ss << n;
        return ss.str();
    }
};

int main()
{
    string s;
    while (cin >> s)
        cout << Solution().solve(s) << endl;
    return 0;
}
