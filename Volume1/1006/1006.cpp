#include <iostream>
using namespace std;

int solve(int p, int e, int i, int d)
{
    int ans = (5544 * p + 14421 * e + 1288 * i) % 21252;
    if (ans <= d)
        ans += 21252;
    return ans - d;
}

int main()
{
    int t = 0;
    int p, e, i, d;
    while (cin >> p >> e >> i >> d && p + e + i + d > -4)
    {
        cout << "Case " << ++t << ": the next triple peak occurs in " <<
            solve(p, e, i, d) << " days." << endl;
    }
    return 0;
}
