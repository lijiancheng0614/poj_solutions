#include <iostream>
#include <cmath>
using namespace std;
const double pi = acos(-1);

void solve()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        double x, y;
        cin >> x >> y;
        int ans = int(pi * (x * x + y * y) * 0.01) + 1;
        cout << "Property " << i + 1 << ": This property will begin eroding in year " <<
            ans << "." << endl;
    }
    cout << "END OF OUTPUT." << endl;
}

int main()
{
    solve();
    return 0;
}
