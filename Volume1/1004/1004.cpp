#include <iostream>
#include <iomanip>
using namespace std;

void solve()
{
    double s = 0;
    for (int i = 0; i < 12; ++i)
    {
        double x;
        cin >> x;
        s += x;
    }
    cout << "$" << setiosflags(ios::fixed) << setprecision(2) << s / 12 << endl;
}

int main()
{
    solve();
    return 0;
}
