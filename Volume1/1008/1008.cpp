#include <iostream>
#include <string>
using namespace std;
string haab[] = {
    "pop", "no", "zip", "zotz", "tzec", "xul", "yoxkin", "mol", "chen", "yax",
    "zac", "ceh", "mac", "kankin", "muan", "pax", "koyab", "cumhu", "uayet"
};
string tzolkin[] = {
    "imix", "ik", "akbal", "kan", "chicchan", "cimi", "manik", "lamat", "muluk",
    "ok", "chuen", "eb", "ben", "ix", "mem", "cib", "caban", "eznab", "canac", "ahau"
};

void solve(int d, string m, int y)
{
    for (int i = 0; i < 19; ++i)
        if (haab[i] == m)
        {
            i = i * 20 + d + y * 365;
            cout << i % 13 + 1 << " " << tzolkin[i % 20] << " " << i / 260 << endl;
            break;
        }
}

int main()
{
    int t;
    cin >> t;
    cout << t << endl;
    while (t--)
    {
        int d, y;
        char c;
        string m;
        cin >> d >> c >> m >> y;
        solve(d, m, y);
    }
    return 0;
}
