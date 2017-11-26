#include <iostream>
using namespace std;

class Solution
{
public:
    int solve(int a1, int a2, int a3, int a4, int a5, int a6)
    {
        int ans = a6 + a5 + a4 + (a3 + 3) / 4;
        int b2 = a4 * 5 + (a3 % 4 ? 7 - (a3 % 4) * 2 : 0);
        if (a2 > b2)
            ans += (a2 - b2 + 8) / 9;
        int b1 = (ans - a6) * 36 - a5 * 25 - a4 * 16 - a3 * 9 - a2 * 4;
        if (a1 > b1)
            ans += (a1 - b1 + 35) / 36;
        return ans;
    }
};

int main()
{
    int a1, a2, a3, a4, a5, a6;
    while (cin >> a1 >> a2 >> a3 >> a4 >> a5 >> a6 && a1 + a2 + a3 + a4 + a5 + a6 > 0)
        cout << Solution().solve(a1, a2, a3, a4, a5, a6) << endl;
    return 0;
}
