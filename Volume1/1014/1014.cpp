#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    bool solve(vector<int> a)
    {
        int n = a.size();
        int s = 0;
        for (int i = 0; i < n; ++i)
            s += a[i] * (i + 1);
        if (s % 2 != 0)
            return false;
        s /= 2;
        vector<int> f(s + 1, -1);
        f[0] = 0;
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 0; j <= s; ++j)
                if (f[j] >= 0)
                    f[j] = a[i - 1];
                else if (j < i || f[j - i] <= 0)
                    f[j] = -1;
                else
                    f[j] = f[j - i] - 1;
            if (f[s] >= 0)
                return true;
        }
        return false;
    }
};

int main()
{
    int t = 0;
    while (true)
    {
        int s = 0;
        vector<int> a(6, 0);
        for (int i = 0; i < 6; ++i)
        {
            cin >> a[i];
            s += a[i];
        }
        if (s == 0)
            break;
        cout << "Collection #" << ++t << ":" << endl;
        if (Solution().solve(a))
            cout << "Can be divided." << endl << endl;
        else
            cout << "Can't be divided." << endl << endl;
    }
    return 0;
}
