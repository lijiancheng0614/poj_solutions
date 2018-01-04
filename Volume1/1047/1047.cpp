#include <iostream>
#include <string>
using namespace std;
class Solution
{
public:
    bool is_cyclic(string & x)
    {
        int n = x.length();
        int s = 0;
        for (int i = n - 1; i >= 0; --i)
        {
            s += (x[i] - '0') * (n + 1);
            if (s % 10 != 9)
                return false;
            s /= 10;
        }
        return true;
    }
};

int main()
{
    string x;
    while (cin >> x)
    {
        if (Solution().is_cyclic(x))
            cout << x << " is cyclic" << endl;
        else
            cout << x << " is not cyclic" << endl;
    }
    return 0;
}
