#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
typedef pair<int, string> pis;

int getInversion(string s)
{
    int ans = 0, a = 0, c = 0, g = 0;
    for (int i = s.length() - 1; i >= 0; --i)
        if (s[i] == 'A')
        {
            ++a;
        }
        else if (s[i] == 'C')
        {
            ++c;
            ans += a;
        }
        else if (s[i] == 'G')
        {
            ++g;
            ans += a + c;
        }
        else
        {
            ans += a + c + g;
        }
    return ans;
}

void solve()
{
    vector<pis> a;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i)
    {
        string s;
        cin >> s;
        a.push_back(pis(getInversion(s), s));
    }
    sort(a.begin(), a.end());
    for (int i = 0; i < m; ++i)
        cout << a[i].second << endl;
}

int main()
{
    solve();
    return 0;
}
