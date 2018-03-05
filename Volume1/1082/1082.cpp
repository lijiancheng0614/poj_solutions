#include <iostream>
using namespace std;
class Solution
{
public:
    bool solve(int y, int m, int d)
    {
        return (m + d) % 2 == 0 || (d == 30 && (m == 9 || m == 11));
    }
};

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int y, m, d;
        cin >> y >> m >> d;
        cout << (Solution().solve(y, m, d) ? "YES" : "NO") << endl;
    }
    return 0;
}
