#include <iostream>
using namespace std;

void solve(double c)
{
    int n = 2;
    for (double s = 0; s < c; ++n)
        s += 1.0 / n;
    cout << n - 2 << " card(s)" << endl;
}

int main()
{
    double c;
    while (cin >> c && c != 0.00)
        solve(c);
    return 0;
}
