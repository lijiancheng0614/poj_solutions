#include <iostream>
using namespace std;
const int factors[] = {3, 7, 9};
const int period[][4] = {
    1, 3, 9, 7,
    1, 7, 9, 3,
    1, 9, 1, 9,
    6, 2, 4, 8
};
class Solution
{
public:
    int solve(int n, int m)
    {
        int n2 = f2(n) - f2(n - m);
        int n5 = f5(n) - f5(n - m);
        if (n2 < n5)
            return 5;
        int ans = 1;
        if (n2 > n5)
            ans = (ans * period[3][(n2 - n5) % 4]) % 10;
        for (int i = 0; i < 3; ++i)
        {
            int s = fx(n, factors[i]) - fx(n - m, factors[i]);
            ans = (ans * period[i][s % 4]) % 10;
        }
        return ans;
    }
private:
    inline int f2(int n)
    {
        return n ? n / 2 + f2(n / 2) : 0;
    }
    inline int f5(int n)
    {
        return n ? n / 5 + f5(n / 5) : 0;
    }
    inline int gx(int n, int x)
    {
        return n ? n / 10 + (n % 10 >= x) + gx(n / 5, x) : 0;
    }
    inline int fx(int n, int x)
    {
        return n ? fx(n / 2, x) + gx(n, x) : 0;
    }
};

int main()
{
    int n, m;
    while (cin >> n >> m)
        cout << Solution().solve(n, m) << endl;
    return 0;
}
