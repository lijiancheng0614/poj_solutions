#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Solution
{
public:
    string solve(const string & oct)
    {
        int n = oct.length();
        int m = 0;
        vector<int> a(n * 3, 0);
        for (int i = n - 1; i > 1; --i)
        {
            int s = oct[i] - '0';
            int j;
            for (j = 0; j < m || s; ++j)
            {
                s = s * 10 + a[j];
                a[j] = s / 8;
                s %= 8;
            }
            m = j;
        }
        string dec(m, ' ');
        for (int i = 0; i < m; ++i)
            dec[i] = a[i] + '0';
        return dec;
    }
};

int main()
{
    string oct;
    while (cin >> oct)
        cout << oct << " [8] = 0." << Solution().solve(oct) << " [10]" << endl;
    return 0;
}
